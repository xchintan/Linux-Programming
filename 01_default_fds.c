/************************************************
 *
 *
 *
 *
 *
 ************************************************/

/*Enables GNU specific extentions*/
#define _GNU_SOURCE 

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include <errno.h>

extern char *program_invocation_short_name; 
#define PNAME program_invocation_short_name

#define  errstr(operation,arg) fprintf(stderr, "%s: %s %s : %s", \
							  PNAME, \
							  operation, arg,\
							  strerror(errorno));
								
int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	printf("stdout =  %d\n",STDOUT_FILENO);
	printf("stdin  =  %d\n",STDIN_FILENO);
	printf("stderr =  %d\n",STDERR_FILENO);

 	/* All stdout/stdin/stderr are pointers to struct _IO_FILE*
	 */	
	ret = EXIT_SUCCESS;
label_main_exit:
	return ret; 
}
