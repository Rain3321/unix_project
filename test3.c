#include<fcntl.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
#include<string.h>
void history_function(){
	FILE *rfp;
	int i=1;
	int j,history_num,line;
	struct tm *tm;
	int leng = 1;
	char buf[BUFSIZ],time_arr[BUFSIZ],real_time[BUFSIZ];
	char output[]={
		"%G-%m-%e_%T"
	};
	time_t tt;
	extern char* optarg;
	
	if((rfp = fopen(".history","r"))==NULL){
		perror("fopen:.history");
		exit(1);
	}
	while(leng++<1024){
		fseek(rfp,-(leng),SEEK_END);
		line = fgetc(rfp);
		if(line == '\n'){
			fgets(time_arr, leng,rfp);
			buf[strlen(buf)-1]='\0';
			printf("%s\n",buf);
		}
	}
	/*while(fgets(buf, BUFSIZ,rfp)!=NULL){
		fgets(time_arr,BUFSIZ,rfp);
		tt = (time_t)(atoi(time_arr));
		tm = localtime(&tt);
		strftime(real_time,BUFSIZ,output,tm);
		printf("%3d %s %s",i,real_time,buf);
		i++;
	}*/
	fclose(rfp);
}
int main(int argc, char *argv[]){
	if(argc==1){
		history_function();
	}
	else if(argc==2){
		if(atoi(argv[1])!=0){
			printf("number\n");
		}
		else
			printf("char\n");
	}
	return 0;
}
