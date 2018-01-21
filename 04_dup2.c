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
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

//dup2(source fd, dest fd)								

int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	int stdout_bkup_fd,new_fd;
	
	stdout_bkup_fd = dup(STDOUT_FILENO);

	new_fd = open("a.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	dup2(new_fd,STDOUT_FILENO); //Overwrite stdout fd
	printf("Hello World \n");
	fflush(stdout);

	dup2(stdout_bkup_fd,STDOUT_FILENO);	//Restore stdout
	printf("Hello there again ..\n");	
	fflush(stdout);


	close(new_fd);
	ret = EXIT_SUCCESS;
label_main_exit:
	return ret; 
}
