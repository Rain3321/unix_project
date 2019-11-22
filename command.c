#include<unistd.h>
#include<stdio.h>
#include<termios.h>
#include<stdlib.h>
#include<fcntl.h>
void cmd_cd(int argc,char *argv[]){
	char wd[BUFSIZ];
	
	chdir(argv[1]);
	return;
}
void cmd_exit(int argc, char *argv[]){
	printf("exit!!!\n");
	exit(0);

}
char get_ch()  
{	
	char ch;
	struct termios buf;  
	struct termios save;  
	tcgetattr(0, &save);  
	buf = save;
	buf.c_lflag &= ~(ICANON|ECHO);  
	buf.c_cc[VMIN] = 1;  
	buf.c_cc[VTIME] = 0;  
	tcsetattr(0, TCSAFLUSH, &buf);
	ch = getchar();
	if(ch != '[') putchar(ch);
	 

	tcsetattr(0, TCSAFLUSH, &save);  
	return ch;
}  




void cmd_history(int argc, char *argv[]){
		FILE *rfp;
		int i,j;
		i=1;
		time_t tt;
		struct tm *tm;
		char buf[BUFSIZ],time_arr[BUFSIZ],real_time[BUFSIZ];
		char output[]={
			"%G-%m-%e_%T"
		};
		if((rfp = fopen(".history","r"))==NULL){
			perror("fopen:.history");
			exit(0);
		}
		while(fgets(buf,BUFSIZ,rfp)!=NULL){
			fgets(time_arr,BUFSIZ,rfp);
			tt = (time_t)(atoi(time_arr));
			tm = localtime(&tt);
			strftime(real_time,BUFSIZ,output,tm);
			printf("%3d %s %s",i,real_time,buf);
			i++;
		}
		fclose(rfp);
		return;
}
