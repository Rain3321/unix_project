#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void checkcommand(int args, char argv[]){
	if(!strcmp(argv[0], "cd")){
		cmd_cd(args, argv[1]);
	}
	return;
}

