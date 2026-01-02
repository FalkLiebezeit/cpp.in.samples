/* reverse.c */
#include <mysql/mysql.h>
#include <string.h>
#define MAX 255
char *
reverse (UDF_INIT * initid, UDF_ARGS * args, char *result,unsigned long *length, char *is_null, char *error) {
	char name_buf[256];
	int i, j;
	char c;

	if (!args->args[0]) {
		/* Return NULL for NULL values */
		*is_null = 1;
		return 0;
	}
	length = args->lengths[0];
	strcpy (name_buf, args->args[0]);
	for (i = 0, j = strlen (name_buf) - 1; i < j; i++, j--) {
		c = name_buf[i];
		name_buf[i] = name_buf[j];
		name_buf[j] = c;
	}
	memcpy (result, name_buf, (int)length);
	result[(int)length] = 0;
	return result;
}

my_bool reverse_init (UDF_INIT * initid,UDF_ARGS * args,char *message) {
	if (args->arg_count == 1)
		args->arg_type[0] = STRING_RESULT;
	else {
		strncpy (message, "UPPER() mit einem Argument aufrufen!",MYSQL_ERRMSG_SIZE);
		return 1;
	}
	initid->max_length = sizeof (args->args[0]);
	initid->maybe_null = 1;
	return 0;
}
