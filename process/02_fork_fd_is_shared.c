#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void foo()
{
    int i;
    for (i=0; i<10; i++) {
        printf("In foo, counting: %d\n", i);
        sleep(1);
    }
}

void bar()
{
    int i;
    for (i=0; i<10; i++) {
        printf("In bar, counting: %d\n", i);
        sleep(1);
    }
}

int main()
{
    pid_t ret;

    ret = fork();
    getchar();
    if (ret == 0) {
        printf("Child process: pid = %d\n", getpid());
        foo();
    } else if (ret > 0) {
        printf("Parent process: pid = %d\n", getpid());
        bar();
    } else {
        perror("fork");
    }


    return 0;
}
