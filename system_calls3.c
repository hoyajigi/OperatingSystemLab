#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char **argv) {
char *c;
int fd0, fd1, sz, seek_cnt;
c = (char *)malloc(100 * sizeof(char));
fd0 = open("printf.txt", O_RDONLY);
fd1 = open("printf-copy.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
if(fd0 < 0 || fd1 < 0) {
perror("Both files");
return 1;
}
/* This is new line; current offset */
seek_cnt = lseek(fd0, 0, SEEK_SET);
printf("Now file offset is %d\n\n", seek_cnt);
sz = read(fd0, c, 40); seek_cnt = lseek(fd0, 0, SEEK_CUR); printf("lseek(%d, 0, SEEK_CUR) returns the current offset = %d\n\n", fd0, seek_cnt); printf("Those bytes are as follows: %s\n\n", c);
printf("Seek back to the beginning of the file, and call read()\n"); lseek(fd0, 0, SEEK_SET);
seek_cnt = lseek(fd0, 200, SEEK_CUR); printf("lseek(%d, 200, SEEK_CUR) returns the current offset = %d\n\n", fd0, seek_cnt);
sz = read(fd0, c, 40); printf("read(%d, c, 10) : result = %d bytes read.\n", fd0, sz);
c[sz] = '\0'; printf("Those bytes are as follows: %s\n\n", c);
close(fd0);
sz = write(fd1, c, strlen(c)); printf("write(%d, c, strlen(c)) : result = %d bytes wrote.\n", fd1, sz); printf("These %d bytes are wrote to file : %s\n", sz, c);
close(fd1);
free(c);
}
