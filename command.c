#include<unistd.h>
#include<stdio.h>
#include<termios.h>
void cmd_cd(int argc,char *argv[]){
	char wd[BUFSIZ];
	
	chdir(argv[1]);
	return;
}
void cmd_exit(int argc, char *argv[]){
	printf("exit!!!\n");
	exit(0);

}
int getch()  
{ 
	int c;
	struct termios buf;  
	struct termios save;  
	tcgetattr(0, &save);  
	buf = save;
	buf.c_lflag &= ~(ICANON|ECHO);  
	buf.c_cc[VMIN] = 1;  
	buf.c_cc[VTIME] = 0;  
	tcsetattr(0, TCSANOW, &buf);
	c=getchar();
	if(c!='[') putchar(c);
	tcsetattr(0, TCSANOW, &save);  
	return c;
}  
