#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[], char *env[])
{
    int i=0;
    
    while(env[i]) {
        printf("%02d:\t%s\n", i+1,env[i]);
		i++;
    }

    return 0;
}

