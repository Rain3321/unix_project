#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int shellcmd(int args, char *argv[]){
	if(!strcmp(argv[0], "cd")){
		cmd_cd(args, argv);
	}
	else if(!strcmp(argv[0], "exit")){
		cmd_exit(args, argv);

	}
	else if(!strcmp(argv[0], "history")){
		cmd_history(args, argv);
	}
	else
		return 0;
	return 1;
}

