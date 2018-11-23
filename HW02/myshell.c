#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void ls(char _in[]){
	int pid = fork();

	if(pid<0){
		printf("fork error \n");
		exit(1);
	}else if( pid==0){
		if( strcmp(_in, "ls")==0){
			execl("/bin/ls", "ls", NULL);
		}
		if( strcmp(_in, "ls -l")==0){
			execl("/bin/ls", "ls", "-l",NULL);
		}
		if( strcmp(_in, "ls -a")==0){
			execl("/bin/ls", "ls", "-a",NULL);
		}
		if( strcmp(_in, "ls -alF")==0){
			execl("/bin/ls", "ls","-alF", NULL);
		}
		if( strcmp(_in, "pwd")==0){
			execl("/bin/pwd", "pwd", NULL);
		}
		if( strcmp(_in, "date")==0){
			execl("/bin/date", "date", NULL);
		}
		if( _in[0]=='r'&&_in[1]=='m'){
			execl("/bin/rm", "rm", _in+3,NULL);
		}
		if( _in[0]=='m'&&_in[1]=='k'&&_in[2]=='d'&&_in[3]=='i'&&_in[4]=='r'){
			execl("/bin/mkdir", "mkdir", _in+6,NULL);
		}
		if( _in[0]=='.'&&_in[1]=='/'){
			execl(_in, _in+2, NULL);
		}
	}else{
		wait(NULL);
		printf("\n");
	}

}

void main(){
	char buf[50];

	printf("------------ My Shell ------------\n\n");

	while(1){
		printf("[MyShell]# ");
		gets(buf);

		if( strcmp(buf, "quit")==0 || strcmp(buf, "q")==0){
			printf("quit..\n\n");
			exit(0);
		}

		if( strcmp(buf, "ls")==0
			||strcmp(buf, "ls -a")==0
			||strcmp(buf, "ls -alF")==0
			||strcmp(buf, "pwd")==0
			||strcmp(buf, "date")==0
			||(buf[0]=='r'&&buf[1]=='m')
			||(buf[0]=='.'&&buf[1]=='/')
			||(buf[0]=='m'&&buf[1]=='k'&&buf[2]=='d'&&buf[3]=='i'&&buf[4]=='r')
			||(strcmp(buf, "ls -l")==0)
			){
			ls(buf);
		}else{
			printf("Command Not Found..\n\n");

		}

	}
}