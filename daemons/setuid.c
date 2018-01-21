#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) 
{
	int uid;

    if (argc < 3) {
        fprintf(stderr, "usage: %s uid program.\n", argv[0]);
        return 1;
    }

    uid = atoi(argv[1]);
    if (setuid(uid) == -1) {
        perror("setuid");
        return 1;
    }
    execl(argv[2], NULL);

	return 0;
}

