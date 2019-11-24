#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void shellcmd(int args, char argv[]){
	if(!strcmp(argv[0], "cd")){
		cmd_cd(args, argv);
	}
	else if(!strcmp(argv[0],"exit")){
		cmd_exit();
	}
	else
		return 0;
	return 1;
}

