#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

extern char etext, edata, end;

int main(int argc, char *argv[]) 
{

	printf("pid =  %d \n",getpid());
    printf("End of Text segment: %p\n"
		   "End of Data: %p\n" 
		   "End of process: %p\n", 
			&etext, &edata, &end);    
    getchar();
    return 0;
}    


