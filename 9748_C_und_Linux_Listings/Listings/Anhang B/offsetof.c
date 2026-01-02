/* offsetof.c */
#include <stdio.h>
#include <stddef.h>
#define MAX 15

struct data {
	char a;
	int b;
	float c;
	double d;
};

int main(void) {
	struct data newfile = { 'a', 1, 1.234, 3E5 };
	struct data *str_ptr = &newfile;
	int offset;

	printf("Start a (%d Bytes)"  ,offsetof(struct data, a));
	printf(" bis b == %d Bytes\n",offsetof(struct data, b));
	printf("Start b (%d Bytes)"  ,offsetof(struct data, b));
	printf(" bis d == %d Bytes\n",offsetof(struct data, d));
	printf("Komplett von Start a (%d Bytes)",
		offsetof(struct data, a));
	printf(" bis Ende d == %d Bytes\n",
		offsetof(struct data, d) + sizeof(double));
	return 0;
}
