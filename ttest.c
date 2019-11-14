#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main(void){
	int num,line_count =0;
	char buffer[128];
	FILE *f;

	num =9;
	f=fopen(".history","r");
	while(fgets(buffer,128,f)!=NULL){
		line_count++;
		if(line_count ==num){
			printf("%s",buffer);
			break;
		}
	}
	fclose(f);
	return 0;
}
