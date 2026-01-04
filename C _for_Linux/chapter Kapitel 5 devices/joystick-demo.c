/* joystick-demo.c */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> // für false/true
#include <string.h> // für sprint()
#include <fcntl.h> // für open() und read()
#include <sys/time.h> // für Timeout-Checks

typedef struct { // extended gaming HID packet (V 2.0)
	unsigned char Buttons;
	unsigned char ExtButtons;
	unsigned char Z;
	unsigned char X;
	unsigned char Y;
	unsigned char AX;
	unsigned char AY;
	unsigned char unused1;
	unsigned char unused2;
};
JoyPacket_t;
JoyPacket_t JoyInfo;
int XCalib;
int YCalib;
// Die nächsten 5 Zeilen gelten nur für den Competition Pro V 2.0.
#define LBUTTON 0x01
#define RBUTTON 0x02
#define LBUTTON_SMALL 0x04
#define RBUTTON_SMALL 0x08
#define RAPIDFIRE_ON 0x10

bool CheckJoyPort(int JoyPort) {
	bool JoyFound=false;
	char DevString[50]; // zusammengesetzter Device-Datei-String
	fd_set set;
	struct timeval timeout;
	int rv,BytesRead,JoyHandle;
	sprintf(DevString,"/dev/hidraw%d",JoyPort); // sprintf() funktioniert.
		analog zu printf()
	JoyHandle=open(DevString,O_NONBLOCK); // Hier muss O_NONBLOCK benutzt werden.
	FD_ZERO(&set); // set initialisieren
	FD_SET(JoyHandle,&set); // set an JoyHandle binden
	timeout.tv_sec=0;
	timeout.tv_usec=100000; // Timeout-Wert für Schnittstelle setzen
	rv=select(JoyHandle,&set,NULL,NULL,&timeout); // Timeout zuweisen
	BytesRead=read(JoyHandle,&JoyInfo,9); // versuchen, 9 Bytes vom Joystick zu lesen
	close(JoyHandle); // JoyHandle entfernen (wichtig)
	if (BytesRead==9) { JoyFound=true; } // Vollständiges Joystick-Paket erhalten?
											Nur dann ist alles OK.
	return JoyFound; // Ist nur true, wenn wirklich 9 Bytes gelesen werden konnten.
}

int FindJoyPort() { // Gibt den Port des ersten gefundenen Joysticks zurück.
	int Port=0; // Start bei /dev/hidraw0	
	for (Port=0; Port<=9; Port++) { // Linux kann bis zu 10 HID-Geräte verwalten.
		if (CheckJoyPort(Port)==true) { break; }
	}
	return Port;
}

void OpenJoyPort(int JoyPort) {
	char DevString[50];
	sprintf(DevString,"/dev/hidraw%d",JoyPort); // sprintf() funktioniert.
		analog zu printf()
	JoyFile=fopen(DevString,"r+b");
}

void CloseJoyPort() {
	fclose(JoyFile);
}

void GetJoyInfo() {
	fread(&JoyInfo,9,1,JoyFile);
}

int main(void) {
	int JoyPort;
	JoyPort=FindJoyPort();
	printf("Joystick an /dev/hidraw%d\n",JoyPort);
	OpenJoyPort(JoyPort);
	XCalib=JoyInfo.X; YCalib=JoyInfo.Y;
	printf("Joystick-Kalibrierung Mitte=(%d,%d)\n",XCalib,YCalib);
	do {
		GetJoyInfo();
		if (JoyInfo.X<(XCalib-64)) { printf(“JOYSTICK LINKS\n"); }
		if (JoyInfo.X>(XCalib+64)) { printf(“JOYSTICK RECHTS\n"); }
		if (JoyInfo.Y<(YCalib-64)) { printf(“JOYSTICK OBEN\n"); }
		if (JoyInfo.Y>(YCalib+64)) { printf(“JOYSTICK UNTEN\n"); }
	}
	while ((JoyInfo.Buttons&LBUTTON)==0);
	printf("Der linke Button wurde gedrückt. Und tschüss ...\n");
	return 0;
}
