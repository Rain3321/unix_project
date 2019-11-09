#include<unistd.h>
#include<stdio.h>
int main(int argc,char *argv[]){
	char wd[BUFSIZ];
	chdir(argv[1]);
	
	getcwd(wd,BUFSIZ);
	printf("Current Directory : %s\n",wd);
	return 0;
}

