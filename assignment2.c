/*
 * 학번 : 2009003039
 * 이름 : 조현석
 * 현재 상태 : 시험기간의 영향으로 눈 밑에는 다크서클이 있고, 사랑니를 뽑아서 입안 전체가 얼얼하다.
 * 제출일 : 2013년 04월 18일
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int norecursive;

void humanReadableBytes(int bytes)
{
	if(bytes>1024*1024*1024){
		printf("%dGiB\n",(int)bytes/1024/1024/1024);
	}
	else if(bytes>1024*1024){
		printf("%dMiB\n",(int)bytes/1024/1024);
	}
	else if(bytes>1024){
		printf("%dKiB\n",(int)bytes/1024);
	}
	else{
		printf("%dBytes\n",bytes);
	}
}

void listDir(char *dirName,int depth) {
	DIR* dir;
	struct dirent *dirEntry;
	struct stat inode;
	char name[1000];
	int i;
	dir = opendir(dirName);
	if (dir == 0) {
		perror ("Error opening directory");
		return;
	}
	while ((dirEntry=readdir(dir)) != 0) {
		if(dirEntry->d_name[0]!=46){ //46은 쩜의 아스키코드이다.		
			sprintf(name,"%s/%s",dirName,dirEntry->d_name);
			lstat (name, &inode);
			
			//현재 디렉토리의 깊이만큼 공백을 출력한다.
			for(i=0;i<depth;i++){
				printf(" ");
			}
			printf("%s", dirEntry->d_name);
			// test the type of file
			if (S_ISDIR(inode.st_mode)){
				printf(" DIRECTORY\n");
				if(!norecursive)
					listDir(name,depth+1);
			}
			else if (S_ISREG(inode.st_mode)){
				printf (" REGULAR_FILE ");
				humanReadableBytes((int)inode.st_size);
			}
			else if (S_ISLNK(inode.st_mode))
				printf (" LINK\n");
			else if (S_ISCHR(inode.st_mode))
				printf (" CHARACTER DEVICE\n");
			else if (S_ISBLK(inode.st_mode))
				printf (" BLOCK DEVICE\n");
			else if (S_ISFIFO(inode.st_mode))
				printf (" PIPE\n");
			else if (S_ISSOCK(inode.st_mode))
				printf (" SOCKET\n");
			else printf(" UNKNOWN INODE\n");
		}
	}
	closedir(dir); //디렉토리를 닫아 주지 않으면 많은 수의 파일을 나열 할 수 없다. 아마도 1024개 제한일 듯
}
int main(int argc, char **argv) {
	char path[200]="./";
	int i;
	if (argc <= 1) {
		printf ("Usage: %s directory_name\n", argv[0]);
		exit(0);
	}
	for(i=1;i<argc;i++){
		if(argv[i][0]!='-'){
			strncpy(path,argv[i],199);
		}
		if(argv[i][1]=='r'){
			norecursive=1;
		}
	}
	if(path[strlen(path)-1] != '/'){
		sprintf(path+strlen(path),"/");
	}
	listDir(path,0);
}
