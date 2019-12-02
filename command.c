#include<unistd.h>
#include<stdio.h>
#include<termios.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
void cmd_cd(int argc,char *argv[]){
	char wd[BUFSIZ];
	
	chdir(argv[1]);
	return;
}
void cmd_exit(int argc, char *argv[]){
	printf("exit!!!\n");
	exit(0);
}
void cmd_history(int argc, char *argv[]){
	int leng =1;
	FILE *rfp;
	int i,line,n;
	i=0;
	time_t tt;
	struct tm *tm;
	char buf[BUFSIZ],time_arr[BUFSIZ],real_time[BUFSIZ];
	char output[]={
		"%G-%m-%e_%T"
	};
	if((rfp = fopen(".history","r"))==NULL){
		perror("fopen:.history");
		exit(1);
	}
	if((n = getopt(argc,argv,"c"))!=-1){
		switch(n){
			case 'c':
				remove(".history");
				break;
			/*default :
				printf("You can only use 'c' option\n");
				break;*/
		}
		}
	if(argc==1){
		while(fgets(buf,BUFSIZ,rfp)!=NULL){
			fgets(time_arr,BUFSIZ,rfp);
			tt = (time_t)(atoi(time_arr));
			tm = localtime(&tt);
			strftime(real_time,BUFSIZ,output,tm);
			printf("%3d %s %s",i+1,real_time,buf);
			i++;
		}
	}
	else if(argc==2){
		if(atoi(argv[1])!=0){
		while(leng++<1024){
			fseek(rfp,-(leng),SEEK_END);
			line = fgetc(rfp);
			if(line == '\n'){
				fgets(buf, leng,rfp);
				buf[strlen(buf)-1]='\0';
				if(atoi(buf)!=0){
					strcpy(time_arr,buf);
					tt = (time_t)(atoi(time_arr));
					tm = localtime(&tt);
					strftime(real_time,BUFSIZ,output,tm);
				}
				else{
					printf("%d %s %s\n",i+1,real_time,buf);
					i++;
				}
			}
			if(i==atoi(argv[1]))
				break;
		} // while(leng++<1024)를 닫는중괄호
		} // if(atoi(argv[1])!=0) 를 닫는 중괄호
/*		else{
			printf("문자입력\n");
			printf("%c\n",n);
			switch(n){
				case 'c':
					remove(".history");
					break;
				case 'm':
					printf("Option : \n");
					printf("'c' : Delete .history file\n");
					printf("n(숫자)을 입력하면 최근에 입력했던 명렁어를 n개 보여줍니다.\n");
					break;
				default :
					printf("You can use 'c','m' option\n");
					break;
			}
			
		}*/
	}
	else
		printf("You can only one option\n");
	fclose(rfp);
	return ;
	
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
