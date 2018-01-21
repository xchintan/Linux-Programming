#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define MATH_LIB_PATH	"./libmath.so.1.1.0"

typedef int (*math_fn_ptr) (int arg);

int main(int argc, char *argv[])
{

    void *handle;
	math_fn_ptr sqr = NULL;
	math_fn_ptr c = NULL;

	printf("pid = %d\n",getpid());
    printf("Press enter to load library...\n");
    getchar();

    handle = dlopen(MATH_LIB_PATH, RTLD_LAZY);
    printf("Press enter to resolve square function...\n");
    getchar();

    sqr = dlsym(handle, "square");
    if (!sqr) {
        fprintf(stderr, "error while resolving square: %s\n",dlerror());
        goto close_handle;
    }

    printf("Press enter to resolve cube function...\n");
    getchar();
    c = dlsym(handle, "cube");
    if (!c) {
        fprintf(stderr, "error while resolving square: %s\n", dlerror());
        goto close_handle;
    }

    printf("sqr = %p, c = %p\n", sqr, c);

    printf("Press enter to call functions...\n");
    getchar();
    printf("Square of 2 is %d\n", sqr(2)); 
    printf("Cube of 3 is %d\n", c(3)); 

    printf("sqr = %p, c = %p\n", sqr, c);

    dlclose(handle);

close_handle:
    dlclose(handle);
exit_program:
    return 0;
}

