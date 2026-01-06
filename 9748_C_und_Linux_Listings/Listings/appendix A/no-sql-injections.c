// no-sql-injections.c
/*
 *  eingabe= die Zeichenkette die geschützt (escaped) werden soll
 *  quote  = das "Quote"-Zeichen - entweder Singe Quote oder
 *           Double Quote, ansonsten wird ein Fehler
 *           zurückgegeben
 *  wc     =  wird hier 0 angegeben, werden Wildcardzeichen
 *            nicht "escaped".
 */
char *escape_sql(const char *eingabe, char quote, int wc) {
	char	*out, *ptr;
	const char *c;

	if (quote != '\'' && quote != '\"')
		return NULL;
	/* Theoretisch könnte jedes Zeichen "escaped" werden,
	 * daher wird zunächst das doppelte an Speicher reserviert */
	if (!(out = ptr = (char *)malloc(strlen(eingabe) * 2 + 2 + 1)))
		return NULL;
	*ptr++ = quote;
	for (c = eingabe;  *c;  c++) {
		switch (*c) {
			case '\'':   /* Single Quote */
			case '\"':   /* Double Quote */
				if (quote == *c) *ptr++ = *c;
				*ptr++ = *c;
			break;
			/* Wildcards */
			case '%':
			case '_':
			case '[':
			case ']':
				if (wc) *ptr++ = '\\';
				*ptr++ = *c;
			break;
			/* Sonderzeichen - Escape-Sequenzen */
			case '\': *ptr++ = '\\'; *ptr++ = '\\'; break;
			case '\b': *ptr++ = '\\'; *ptr++ = 'b';  break;
			case '\n': *ptr++ = '\\'; *ptr++ = 'n';  break;
			case '\r': *ptr++ = '\\'; *ptr++ = 'r';  break;
			case '\t': *ptr++ = '\\'; *ptr++ = 't';  break;
			default:
				*ptr++ = *c;
			break;
		}
	}
	*ptr++ = quote;
	*ptr = '\0';      /* Terminieren */
	return out;
}
