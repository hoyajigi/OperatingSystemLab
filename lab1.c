#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>

int main()
{
	int status;
	pid_t cpid=fork();

	if(cpid==-1){
		perror("fork");
		exit(1);
	}else if(cpid==0){
		printf("Child PID is %d\n",(long)getpid());
		pause();
	}
	else{
		do {
			pid_t w = waitpid(cpid, &status, WUNTRACED | WCONTINUED); 
			if(w == -1) {
				perror("wait pid");
				exit(1);
			}
			if(WIFEXITED(status)) printf("exited, status = %d\n", WEXITSTATUS(status));
			else if(WIFSIGNALED(status))
				printf("killed by signal %d\n",WTERMSIG(status));
			else if(WIFSTOPPED(status))
				printf("stopped by signal %d\n", WSTOPSIG(status));
			else if(WIFCONTINUED(status))
				printf("continued\n");
		} while(!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}

