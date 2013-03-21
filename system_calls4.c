#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#define BLOCKSIZE 256
/* This is simple cp like file copier. */
int main(int argc, char** argv) {
	// command line argv is available
	// so we implement argc check.
	if(argc != 3) {
		/* argv[0] - executable file name
		argv[1] - original file name
		argv[2] - target file name */
		printf("Usage : ./mycopy <original> <target>\n");
		return 1;
	}
	int fd_ori, fd_tar, read_cnt, write_cnt, temp_cnt;
	char *buffer;
	printf("Open file1, file2 : ");
	fd_ori = open(argv[1],O_RDONLY );
	fd_tar = open(argv[2],O_CREAT|O_RDWR|O_APPEND,0644 );
	if(fd_ori < 0 || fd_tar < 0) {
		printf("failed. %d, %d\n", fd_ori, fd_tar);
		return 1;
	} else {
		printf("OK.\n");
	}
	/* offset initialize */
	lseek(fd_ori,0,SEEK_SET );
	lseek(fd_tar,0,SEEK_SET );
	buffer = (char *)malloc(BLOCKSIZE * sizeof(char));
	do {
		temp_cnt = read(fd_ori,buffer,BLOCKSIZE );
		printf("read:\t %d bytes / Total:\t %d bytes\n", temp_cnt, read_cnt =+ temp_cnt);
		buffer[temp_cnt] = '\0';
		write(fd_tar,buffer,temp_cnt );
	} while(temp_cnt != 0);
	close(fd_ori);
	close(fd_tar);
}
