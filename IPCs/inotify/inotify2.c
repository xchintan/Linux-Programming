#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>
#include <unistd.h>

#define EVENT_SIZE  (sizeof (struct inotify_event))
#define EVENT_BUF_LEN     (1024 * (EVENT_SIZE + 16))

int main(int argc, char **argv)
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[EVENT_BUF_LEN];

  if (argc < 2) {
    fprintf(stderr, "usage: %s path.\n", argv[0]);
    return EXIT_FAILURE;
  }

  if ((fd = inotify_init()) < 0) {
    perror("inotify_init");
    return EXIT_FAILURE;
  }

  wd = inotify_add_watch(fd, argv[1], IN_CREATE | IN_DELETE);

  while (1) {
      if ((length = read(fd, buffer, EVENT_BUF_LEN)) == -1) {
        perror("read");
        return EXIT_FAILURE;
      }  

      printf("Event size read: %u\n", length);
      i = 0;
      while (i < length) {     
        struct inotify_event *event = (struct inotify_event *) &buffer[i];
        if (event->len) {
          if (event->mask & IN_CREATE) {
            if (event->mask & IN_ISDIR) {
              printf( "New directory %s created.\n", event->name );
            } else {
              printf( "New file %s created.\n", event->name );
            }
          } else if ( event->mask & IN_DELETE ) {
            if ( event->mask & IN_ISDIR ) {
              printf( "Directory %s deleted.\n", event->name );
            } else {
              printf( "File %s deleted.\n", event->name );
            }
          }
        }
        i += EVENT_SIZE + event->len;
      }
  }
  inotify_rm_watch(fd, wd);

  close(fd);
  return EXIT_SUCCESS;
}
