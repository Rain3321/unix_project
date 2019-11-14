#include "smallsh.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>

static char inpbuf[MAXBUF], tokbuf[2*MAXBUF],	*ptr, *tok;

static char special[] = {' ', '\t', '&', ';', '\n', '\0'};
char *prompt = "Command>";	/* Prompt */

/*	프롬프트(prompt)를 인쇄하고 키보드에서 한 줄의		*/
/*	입력이 들어오기를 기다린다. 받은 입력은 무엇이건	*/
/*	프로그램 버퍼에 저장한다.					*/
userin(char *p) //명령어 입력해서 저장  inpbuf에 저장하는 거임 마지막에 \0 리턴값으로 메인문 반복 지속
{
	int c, count;
	/* initialization for later routines */
	ptr = inpbuf;
	tok = tokbuf;
	int check;
	char  outbuf[256];
	int fd;
	time_t tt;
	char timebuf[12];
	if((fd = open("/data3/2019/3c2/s151937/project/.history", O_CREAT | O_RDWR | O_APPEND, 0644)) == -1) {
			perror("open");
			exit(1);
			}

			/* display prompt */
			printf("%s ", p); //command> 가 출력
			count = 0;
			while(1) {
			if (((c = getchar()) == EOF)) return(EOF); //-1이나 ctRl+c  
			if (count < MAXBUF) inpbuf[count++] = c;//명령어를 inpbuf에 넣는다
			
			if (c == '\n' && count < MAXBUF) {
			inpbuf[count] = '\0';
			// printf(" inpbuf[%d] : %s \n", count, inpbuf);
				if(write(fd, inpbuf, count) != count) perror("Write");
				time(&tt);
				sprintf(timebuf, "#%d\n",(int)tt); 
				write(fd, timebuf, 12); 
				close(fd);

			return(count);
			}
			/*  if line too long, restart */
			if (c == '\n') {
				printf(" smallsh : input line too long\n");
				count = 0;
				printf("%s ", p); //다시 command> 출력
			}
			}
}
/* get token and place into tokbuf */
gettok(char **outptr)
{
	int type;
	/* outptr 문자열을 tok 로 지정한다 */
	*outptr = tok;

	/* 토큰을 포함하고 있는 버퍼로부터 여백을 제거한다 */
	while( *ptr == ' ' || *ptr == '\t') ptr++;

	/* 토큰 포인터를 버퍼 내의 첫 토큰으로 지정한다 */
	*tok++ = *ptr;

	/* 버퍼내의 토큰에 따라 유형 변수를 지정한다 */
	switch(*ptr++) {
		case '\n' : type = EOL;
					/* printf(" type == EOL getok()\n"); */
					break;
		case '&'  :	
					type = AMPERSAND;
					/* printf(" type == AMPERSAND getok()\n"); */
					break;
		case ';'  :	type = SEMICOLON;
					/* printf(" type == SEMICOLON getok()\n"); */
					break;
		default   :	type = ARG;
					/* printf(" type == ARG getok()\n"); */
					while(inarg(*ptr)) 
						*tok++ = *ptr++;
	}
	*tok++ = '\0';
	return type;
}

/* are we in an ordinary argument , 일반적인 인자일 때 */
inarg(c)
	char c;
{
	char *wrk;

	for(wrk = special; *wrk != '\0'; wrk++) {
		if (c == *wrk) {
			printf(" special arg : %c inarg()\n", *wrk);
			return(0);
		}
	}

	return(1);
}

/*		입력 줄을 아래와 같이 처리한다 :				*/
/*									*/
/*	gettok을 이용하여 명령문을 구무분석(parse) 하고		*/
/*	그 과정에서 인수의 목록을 작성한다. 개행문자나		*/
/*	세미콜론(;)을 만나면 명령을 수행하기 위해			*/
/*	runcommand라 불리는 루틴을 호출한다.				*/
procline() 
{
	char *arg[MAXARG+1];	/* runcommand를 위한 포인터 배열 */
	int toktype;			/* 명령내의 토근의 유형 */
	int narg;			/* 지금까지의 인수 수 */
	int type;			/* FOREGROUND or BACKGROUND */
		
	/* 토큰 유형에 따라 행동을 취한다.	*/
	for (narg = 0;;) {	/* loop FOREVER */
		switch(toktype = gettok(&arg[narg])) {
			case ARG	: if (narg < MAXARG) narg++;
							  break;
			case EOL	: 
			case SEMICOLON	: 
			case AMPERSAND	: 
						  type = (toktype == AMPERSAND) ? BACKGROUND : FOREGROUND;
						  if (narg != 0) { //\n이나 ;를 만나면 command 실행
							  arg[narg] = NULL;
							  runcommand(arg, type);
						  }

						  if (toktype == EOL) return;
						  narg = 0;
						  break;
		}
	}

}

/*	 wait를 선택사항으로 하여 명령을 수행한다.		*/
/*	명령을 수행하기 위한 모든 프로세스를 시작하게 한다.		*/
/*	만일 where가 smallsh.h에서 정의된 값 BACKGROUND로	*/
/*	지정되어 있으면 waitpid 호출은 생략되고 runcommand는 */
/*	단순히 프로세스 식별번호만 인쇄하고 복귀한다.		*/
runcommand(cline, where)
	char **cline;
	int where;
{
	int pid, exitstat, ret;
	int status;

	if(shellcmd(where, cline)) return 0;
	//if(!strcmp(*cline, "cd")) cmd_cd(where, cline);
	//else if(!strcmp(*cline, "exit")) cmd_exit(where, cline);
	if ((pid = fork()) < 0) {
		perror("smallsh");
		return(-1);
	}
	//else {
		if (pid == 0) {	/* child */
		execvp(*cline, cline);
		perror(*cline);
		exit(0);
		
	}

	/* code for parent */
	/* if background process, print pid and exit */
	if (where == BACKGROUND) {
		printf("[Process id %d]\n",pid);
		return(0);
	}

	/* 프로세스 pid가 퇴장할 때까지 기다린다. */
	if (waitpid(pid, &status, 0) == -1)
		return (-1);
	else 
		return (status);
	//}
}

main()
{
	while(userin(prompt) != EOF)
		procline();
}

