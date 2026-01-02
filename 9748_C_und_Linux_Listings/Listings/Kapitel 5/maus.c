/* maus.c */
#include<stdio.h> // für printf()
#include<fcntl.h> // für open()
#include<unistd.h> // für read()
#include<stdbool.h> // für bool

#define MB_LEFT 0x01
#define MB_RIGHT 0x02
#define MB_MID 0x04
typedef struct {
	char Buttons;
	char X;
	char Y;
}
MouseInfo_t;
MouseInfo_t MI;
int XMouse=0,YMouse=0,MouseButtons=0;

bool LButton() {
	if ((MouseButtons&MB_LEFT)==MB_LEFT) { return true; }
	else { return false; }
}

bool RButton() {
	if ((MouseButtons&MB_RIGHT)==MB_RIGHT) { return true; }
	else { return false; }
}

bool MButton() {
	if ((MouseButtons&MB_MID)==MB_MID) { return true; }
	else { return false; }
}

int main(void) {
	int MouseHandle,BytesRead;
	MouseHandle=open("/dev/hidraw2",O_RDONLY,O_NONBLOCK); // Pfad evtl. ändern
	while (LButton()==false) {
		BytesRead=read(MouseHandle,&MI,3);
		if (BytesRead!=-1) {
			if ((MI.X&0x80)==0x80) { XMouse+=-((~MI.X)&0x7f); }
			else { XMouse+=MI.X; }
			if ((MI.Y&0x80)==0x80) { YMouse+=-((~MI.Y)&0x7f); }
			else { YMouse+=MI.Y; }
			if (XMouse<0) { XMouse=0; }
			if (YMouse<0) { YMouse=0; }
			MouseButtons=(long int)(MI.Buttons);
			printf("X=%ld Y=%ld B=%ld\n",Xmouse,Ymouse,MouseButtons);
		}
	}
	printf("Die linke Maustaste wurde gedrückt, also tschüss ...\n");
	return 0;
}

