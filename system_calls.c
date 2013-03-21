#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
int main() {
int fd0, fd1;
char s[50] = "This will be output to file.dat\n";
char err[50] = "There was an error writing to file.dat\n";
// Open or create file
fd0 = open("file.dat", O_CREAT | O_WRONLY | O_APPEND, 0644);
if(fd0 < 0) {
printf("Cannot open \"file.dat\" \n");
return 1;
}
if(write(fd0, s, strlen(s)) != strlen(s)) {
write(stdout, err, strlen(err));
return 1;
}
close(fd0);
return 0;
}
