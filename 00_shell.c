
#define _GNU_SOURCE 

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>
#include<readline/readline.h> /*GNU Library*/
#include<readline/history.h>  
#include<wordexp.h>			/*POSIX Compliant*/

int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	char *input;
	pid_t ch_pid = 0;
	int status;
	wordexp_t words; //we're intesteed in words.we_wordc words.we_wordv
	
	 while(input = readline("enginex-cmd#")){
		if(wordexp(input,&words,0)) {
			printf("error while parsing command\n");
			continue;
		}
		ch_pid = fork();

		if(0==ch_pid) {
			/*Child process*/
			ret = execvp(words.we_wordv[0],words.we_wordv);
			if(ret==-1) {
				printf(" execvp failded for: %s\n",words.we_wordv[0]);
				exit(1);
			}

		} else if(ch_pid > 0){ /*Parent Process*/
			wait(&status);
		}
		add_history(input); /*Add command to history*/
		wordfree(&words);
	}
	ret = EXIT_SUCCESS;
label_main_exit:
	return ret; 
}
