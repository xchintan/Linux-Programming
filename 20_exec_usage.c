#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{

    execlp("./progname", "Welcome", "Hello world", NULL);

/*    execlp("/bin/ls", "/bin/ls", "-l", "/usr", NULL); */
    /* /bin/ls -l /usr */
    return 0;
}
