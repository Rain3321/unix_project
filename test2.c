#include<fcntl.h>
#include<time.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<ctype.h>
void history_function(int argc, char *argv[]){
	FILE *rfp;
	int i=1;
	int j,history_num;
	struct tm *tm;
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
	while(fgets(buf, BUFSIZ,rfp)!=NULL){
		fgets(time_arr,BUFSIZ,rfp);
		tt = (time_t)(atoi(time_arr));
		tm = localtime(&tt);
		strftime(real_time,BUFSIZ,output,tm);
		printf("%3d %s %s",i,real_time,buf);
		i++;
	}
	fclose(rfp);
}
int main(int argc, char *argv[]){
	printf("%d",argc);
	printf("%s",argv[1]);
	return 0;
}
