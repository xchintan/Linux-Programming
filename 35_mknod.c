#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
int main(int argc, char *argv[]) 
{

    /*
    * S_IFCHR -> Char
    * S_IFBLK -> Block
    * S_IFIFO -> FIFO
    * S_IFSOCK -> Socket
    * S_IFREG -> Regular file
    */
    return mknod(argv[1], S_IFCHR | 0644, makedev(14, 4));
}

