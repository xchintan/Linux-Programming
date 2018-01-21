#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

extern char *program_invocation_name;
extern char *program_invocation_short_name;

#define error(x, y) fprintf(stderr, "%s: error while %s on %s: %s\n" \
                       program_invocation_short_name, x, y, strerror(errno))

int main(int argc, char *argv[]) 
{
    int ret = EXIT_FAILURE;

    int ch;

    ch = getchar();
    printf("ch = %c\n", ch);

    ret = EXIT_SUCCESS;

exit_program:
    return ret;
}    


