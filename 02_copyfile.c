#define _GNU_SOURCE // Enables GNU specific extentios  such as program_invocation_short_name 
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#include <errno.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


//Defined in libc - captures 'prgoram name'- use this to capture 
// program name in outside main. (Functions not having argv[0])
extern char *program_invocation_short_name; 
#define PNAME program_invocation_short_name

/* Error:
	1) Develop a habit to write error to always stderr not stdout
	2) Try to write error like linux CLIs
	Example: 
		ls: cannot access x: No such file or director
*/
#define  errstr(msg,arg) fprintf(stderr, "%s: %s %s : %s\n", \
							  PNAME, \
							  msg, arg,\
							  strerror(errno));
								
int main(int argc, char **argv) {
	int ret = EXIT_FAILURE;
	char *srcfile = NULL;
	char *dstfile = NULL;
	char *buf = (char*)malloc(1024);
	int src_fd = 0;
	int dst_fd = 0;
	int nread = 0;
	int nwrite = 0;

	if(argc != 3) {
		fprintf(stderr,"usage: %s  soruce destination \n", PNAME);
		goto label_main_exit;
	}

	printf("%s %s %s\n",PNAME,argv[1],argv[2]);
	
	srcfile = argv[1];
	dstfile = argv[2];

	if((src_fd = open(srcfile,O_RDONLY)) == -1) {
		errstr("error while opening", srcfile);
		goto label_main_exit;

	}
	if((dst_fd = open(dstfile,O_CREAT | O_WRONLY | O_EXCL)) == -1) {
		errstr("error while creating", dstfile);
		goto label_main_close_src;
	}

	do {
		//Skipping all the error checking..
		nread = read(src_fd,buf,1024);
		nwrite = write(dst_fd,buf,nread);
	}while(nread);

	ret = EXIT_SUCCESS;
label_main_close_dst:
	close(dst_fd);
label_main_close_src:
	close(src_fd);
label_main_exit:
	return ret; 
}
