#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE	40

int main(void){
	int fd;
	
	char* in = (char*)malloc(sizeof(char) * MAX_SIZE);
	char* out = (char*)malloc(sizeof(char) * MAX_SIZE);
	
	if( (fd=open("/dev/mydevicefile", O_RDWR))<0 ){
		perror("open error");
		return -1;
	}
	int i = 0;
	int num = 0;
	char c;
	char s[40];
	while(1){
		printf("Do you want to input information?[Y/N]");
		scanf("%c",&c);
		fflush(stdin);
		if(c=='N')break;
		else{
		printf("Write student's Name, Phone number, Student Number :");
		fgets(s, sizeof(s), stdin);
		fgets(s, sizeof(s), stdin); s[strlen(s)-1] = '\0';
		strcpy(out,s);
		write(fd,out,MAX_SIZE);
		num++;
	}}
	printf("\n\nPRINTING INFORMATIONS\n");
	for (i = 0; i<num; i++){
	read(fd, in, MAX_SIZE);	printf("%s \n", in);
	}
	free(in);
	free(out);

	close(fd);
	return 0;
}

