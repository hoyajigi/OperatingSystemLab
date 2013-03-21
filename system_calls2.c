#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char **argv)
{
char *c;
int fd0, fd1, sz;
c = (char *)malloc(100 * sizeof(char));
fd0 = open("printf.txt", O_RDONLY);
fd1 = open("printf-copy.txt", O_CREAT | O_RDWR | O_APPEND, 0644);
if(fd0 < 0 || fd1 < 0)
{
perror("Both files");
return 1;
}
sz = read(fd0, c, 10);
printf("read(%d, c, 10) : result = %d bytes read.\n", fd0, sz);
c[sz] = '\0';
printf("Those bytes are as follows: %s\n", c);
close(fd0);
sz = write(fd1, c, strlen(c));
printf("write(%d, c, strlen(c)) : result = %d bytes wrote.\n", fd1, sz);
printf("These %d bytes are wrote to file : %s\n", sz, c);
close(fd1);
free(c);
}
