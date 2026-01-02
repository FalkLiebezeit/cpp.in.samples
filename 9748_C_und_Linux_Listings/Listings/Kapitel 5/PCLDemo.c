/* PCLDemo.c */
#include<stdio.h>
#include<string.h>

FILE *LPT;

void Print(char *Line) { // Druckt eine Zeile aus, ohne CR/LF auszuführen.
	fwrite(Line,strlen(Line),1,LPT); // String
}

void PrintLN(char *Line) { // Druckt eine Zeile aus und führt auch CR/LF aus.
	int C;
	fwrite(Line,strlen(Line),1,LPT); // String
	C='\n'; fwrite(&C,1,1,LPT); // LF
	C='\r'; fwrite(&C,1,1,LPT); // CR
}

void SetCol(int Col) { // Setzt den virtuellen Textcursor in die Spalte [Col].
		(nur PCL-Drucker)
	char Line[256];
	sprintf(Line,"\e&a%dC",Col); // SetCol=ESC+&+a, Terminator=C,
	Parameter=[column]
	fwrite(&Line,strlen(Line),1,LPT);
}

void EndPage() { // Wirft die Seite aus, die aktuell im Puffer ist.
	char Line[256];
	sprintf(Line,"\f"); // EOP=\f (0x0C)
	fwrite(&Line,strlen(Line),1,LPT);
}

void EndDoc() { // Beendet den Druckauftrag (die BUSY-Lampe muss
				anschließend erlöschen).
	char Line[256];
	sprintf(Line,"\eE"); // EOT=ESC+E
	fwrite(&Line,strlen(Line),1,LPT);	
}

int main(void) {
	int i=0;
	char Line[256];
	LPT=fopen("/dev/usb/lp0","r+b"); // Bei USB-Druckern /dev/usb/lp0
	for (i=0; i<50; i++) {
		Print("i ist jetzt");
		SetCol(40);
		sprintf(Line,"%d",i); PrintLN(Line);
	}
	PrintLN("<Ende der Schleife>");
	PrintLN("<Druckjob beendet>");
	EndPage(); EndDoc();
	fclose(LPT);
	return 0;
}

