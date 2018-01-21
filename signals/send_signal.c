#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main(int argc, char **argv)
{
	int sig, pid;

	if (argc < 3) {
		fprintf(stderr, "usage: %s signal pid\n", argv[0]);
		return 1;
	}

	sig = atoi(argv[1]);
	pid = atoi(argv[2]);

	if (kill(pid, sig) == -1) {
		fprintf(stderr, "%s: kill %s: %s", argv[0], argv[2], 
			       strerror(errno));	

		return 1;
	}

	return 0;
}
