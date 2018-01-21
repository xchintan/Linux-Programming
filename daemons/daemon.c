#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <signal.h>

void clean_exit(int sig)
{
	syslog(LOG_INFO, "Daemon exiting...\n");
	unlink("/var/run/daemon.pid");
	exit(0);

}

void daemonize()
{
	int i = 0;
	char logmessage[512];
	int len;

	signal(SIGTERM, clean_exit);
	
	close(0);
	close(1);
	close(2);
	
	setsid();

	openlog("test daemon", LOG_PID, LOG_DAEMON);

    chdir("/");
	syslog(LOG_NOTICE, "Daemon started...\n");
	while (1) {
		syslog(LOG_NOTICE, "Counting %d\n", i++);
		sleep(3);
	}
}


int main()
{
	pid_t pid;
	int pid_file;
	int len;
	char pid_num[8];

	pid = fork();
	if (pid == 0) {
		daemonize();
	} else if (pid > 0) {
		printf("Daemon started on pid: %u\n", pid);

		pid_file = open("/var/run/daemon.pid", O_CREAT | O_WRONLY, 0644);
		len = sprintf(pid_num, "%u", (unsigned int)pid);
		write(pid_file, pid_num, len);
        close(pid_file);	

	}

	return 0;
}

