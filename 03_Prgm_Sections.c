#include <stdio.h>
#include <stdlib.h>

char  glbl_initalized[] = "Hello world"; 		/*  RW Data rw- */
char  *glbl_ro  	  		= "Test string"; 	/*  RO Data r-- */
char  glbl_uninitalized[100];             		/*  BSS  rw- */
static int glbl_static = 0;

/*  code goes to text segment  r-x */
int main()  
{
    char local_stack[] = "New string"; 		/*  Stack rw- */
    char *ptr_to_txt   = "Another string"; 	/* ptr1 -> Stack, Another string -> RO Data */
    char *heap;                     		
    static int local_static;                 /*  BSS  */
    
	heap = (char *)malloc(100);

	printf("STACK:\tLocal Variables\t\t= %p\n\n",local_stack);
	
	printf("Heap:\tHeap Variables\t\t= %p\n\n",heap);

	printf("BSS:\tGlobal Un-initialized\t= %p\n",glbl_uninitalized);
	printf("BSS:\tGlobal Static\t\t= %p\n",&glbl_static);
	printf("BSS:\tLocal Static\t\t= %p\n\n",&local_static);

	printf("DataRW:\tGlobal Initialized\t= %p\n\n",glbl_initalized);

	printf("TXT:\tGlobal Read Only\t= %p\n",glbl_ro);
	printf("TXT:\tLocal Pointing to TXT\t= %p\n",ptr_to_txt);
    getchar();

    return 0;
}    


