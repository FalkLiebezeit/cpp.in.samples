/* my_cgi.h */
#define MAX_PAARE 255
#define BUF 255

char *getdata( void );
char *Strdup(const char *);
void hex2ascii(char *);
char convert(char *);
struct CGI_DATEN *erstellen(char *);

struct CGI_DATEN {
	char *variable;
	char *wert;
	struct CGI_DATEN *next;
};

struct CGI_DATEN *ende = NULL;

/*
 *  Funktion liest Daten in der POST- oder GET-Methode ein.
 *  Rückgabewert: Stringpuffer mit den Daten
 *  bei Fehler  : NULL
*/
char *getdata() {
	unsigned long size;
	char *puffer = NULL;
	char *request = getenv("REQUEST_METHOD");
	char *cont_len;
	char *cgi_string;

	/* Zuerst die Request-Methode überprüfen */
	if(  NULL == request )
		return NULL;
	else if( strcmp(request, "GET") == 0 ) {
		/* Die Methode GET -> Query-String abholen */
		cgi_string = getenv("QUERY_STRING");
		if( NULL == cgi_string )
			return NULL;
		else {
			puffer =(char *) Strdup(cgi_string);
			return puffer; /* Rückgabewert an den Aufrufer */
		}
	}
	else if( strcmp(request, "POST") == 0 ) {
		/* Die Methode POST -> Länge des Strings
		ermitteln (CONTENT_LENGTH) */
		cont_len = getenv("CONTENT_LENGTH");
		if( NULL == cont_len)
			return NULL;
		else { /* String CONTENT_LENGTH in
			unsigned long umwandeln */
			size = (unsigned long) atoi(cont_len);
			if(size <= 0)
				return NULL; /* Keine Eingabe!?!? */
		}
		/* Jetzt lesen wir die Daten von stdin ein */
		puffer =(char *) malloc(size+1);
		if( NULL == puffer )
			return NULL;
		else {
			if( NULL == fgets(puffer, size+1, stdin) ) {
				free(puffer);
				return NULL;
			}
			else   /* Rückgabewerte an den Ausrufer */
			return puffer;
		}
   	 }
	/* Weder GET-Methode noch die POST-Methode wurden verwendet */
	else
		return NULL;
}

/*
 *  Da die Funktion strdup() in der Headerdatei <string.h> keine
 *  ANSI C-Funktion ist, schreiben wir eine eigene
 */
char *Strdup(const char *str) {
	char *p;
	if(NULL == str)
		return NULL;
	else {
		p =(char *) malloc(strlen(str)+1);
		if(NULL == p)
		return NULL;
	else
		strcpy(p, str);
	}
	return p;
}

/* Wandelt einzelne Hexzeichen (%xx) in ASCII-Zeichen
   und kodierte Leerzeichen (+) in echte Leerzeichen um */
void hex2ascii(char *str) {
	int x,y;
	for(x=0,y=0; str[y] != '\0'; ++x,++y) {
		str[x] = str[y];
		/* Ein hexadezimales Zeichen ? */
		if(str[x] == '%') {
			str[x] = convert(&str[y+1]);
			y+=2;
		}
		/* Ein Leerzeichen? */
		else if( str[x] == '+')
			str[x]=' ';
	}
	/* Geparsten String sauber terminieren */
	str[x] = '\0';
}

/* Funktion konvertiert einen String von zwei hexadezimalen
   Zeichen und gibt das einzelne dafür stehende Zeichen zurück
 */
char convert(char *hex) {
	char ascii;

	/* erster Hexwert */
	ascii =(hex[0] >= 'A' ? ((hex[0] & 0xdf) - 'A')+10 : (hex[0] - '0'));
	/* Bitverschiebung schneller als ascii*=16 */
	ascii <<= 4;
	/* zweiter Hexwert */
	ascii +=(hex[1] >= 'A' ? ((hex[1] & 0xdf) - 'A')+10 : (hex[1] - '0'));
	return ascii;
}

/* Liste aus Variablen/Wertpaaren erstellen
 * Rückgabewert: Anfangsadresse der Liste
 * Bei Fehler: NULL
 */
struct CGI_DATEN *erstellen(char *str) {
 	char* s;
	char* res;
	/* Irgendwo gibt es auch eine Grenze, hier sind
	MAX_PAARE erlaubt */
	char *paare[MAX_PAARE];
	struct CGI_DATEN *ptr_daten = NULL;
	struct CGI_DATEN *ptr_anfang = NULL;
	int i=0, j=0;

	/* Zuerst werden die Variablen/Wertpaare anhand des Zeichens
	 '&' getrennt, sofern es mehrere sind  */
	s=str;
	res=strtok(s,"&");
	while( res != NULL && i < MAX_PAARE) {
		/* Wert von res dynamisch in char **pair speichern */
		paare[i] = (char *)malloc(strlen(res)+1);
		if(paare[i] == NULL)
			return NULL;
		paare[i] = res;
		res=strtok(NULL,"&");
		i++;
	}

	/* Jetzt werden die Variablen von den Werten getrennt und
   	an die Struktur CGI_DATEN übergeben */
	while ( i > j ) {/* Das erste Element? */
		if(ptr_anfang == NULL) {
			ptr_anfang =(struct CGI_DATEN *)
			malloc(sizeof (struct CGI_DATEN *));
			if( ptr_anfang == NULL )
				return NULL;
			res = strtok( paare[j], "=");
			if(res == NULL)
				return NULL;
			ptr_anfang->variable =(char *)malloc(strlen(res)+1);
			if( ptr_anfang->variable == NULL )
				return NULL;
			ptr_anfang->variable = res;
			res = strtok(NULL, "\0");
			if(res == NULL)
				return NULL;
			ptr_anfang->wert =(char *) malloc(strlen(res)+1);
			if( ptr_anfang->wert == NULL )
				return NULL;
			ptr_anfang->wert = res;
			/* printf("%s %s<br>",ptr_daten->variable,ptr_daten->wert); */
			ptr_anfang->next = (struct CGI_DATEN *)malloc(sizeof (struct CGI_DATEN *));
			if(ptr_anfang->next == NULL)
				return NULL;
			ptr_daten = ptr_anfang->next;
			j++;
		}
		else {   /* Die restlichen Elemente */
			res = strtok( paare[j], "=");
			if(res == NULL)
				return NULL;
			ptr_daten->variable =(char *)malloc(strlen(res)+1);
			if(ptr_daten->variable == NULL)
				return NULL;
			ptr_daten->variable = res;
			res = strtok(NULL, "\0");
			if(res == NULL)
				return NULL;
			ptr_daten->wert =(char *) malloc(strlen(res)+1);
			if(ptr_daten->wert == NULL)
				return NULL;
			ptr_daten->wert = res;
			/* printf("%s %s<br>",ptr_daten->variable,
			ptr_daten->wert);*/
			ptr_daten->next = (struct CGI_DATEN *)malloc(sizeof (struct CGI_DATEN *));
			if( ptr_daten->next == NULL )
				return NULL;
			ptr_daten = ptr_daten->next;
			j++;
		}
	}
	ende = ptr_daten;
	/* Anfangsadresse der Liste struct CGI_DATEN zurückgeben */
	return ptr_anfang;
}
