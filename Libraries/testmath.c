#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

extern int square(int x);
extern int cube(int x);

int main()
{
	printf("pid = %d\n",getpid());
    printf("Square of 2 = %d\n", square(2));
    printf("Cube of 3 = %d\n", cube(3));
	getchar();
    return 0;
}    



