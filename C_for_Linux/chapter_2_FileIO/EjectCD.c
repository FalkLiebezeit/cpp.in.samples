/* EjectCD.c */
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h.>
#include <linux/cdrom.h>

/* Bitte anpassen, falls notwendig. */
#define CDROM "/dev/cdrom"

int main(int argc, char **argv) {
	int fd, rc;
	if((fd = open(CDROM, O_RDONLY)) < 0) {
		fprintf(stderr, "Konnte %s nicht öffnen\n",CDROM);
		return 1;
	}
	if((rc = ioctl(fd, CDROMEJECT)) != 0) {
		perror("Konnte CD-ROM nicht auswerfen\n");
		return 1;
	}
	close(fd);
	return 0;
}
