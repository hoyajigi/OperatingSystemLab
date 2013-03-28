#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
/* "Define statement" It makes you easy while programming */
#define RWRWRW (S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)
int main(int argc, char **argv) {
	/* set default umask value */
	umask(0);
	if (creat("foo", RWRWRW) < 0)
		perror("creat error for foo");
	/* change default umask value */
	umask(S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
	if (creat("bar", RWRWRW) < 0)
		perror("creat error for bar");
	exit(0);
}
