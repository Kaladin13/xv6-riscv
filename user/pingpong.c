#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  dump();

  // int descriptors[2];

  // pipe(descriptors);

  // int pid = fork();

  // if (pid == 0)
  // {
  //   // child
  //   int child_pid = getpid();

  //   char buffer[10];

  //   read(descriptors[0], buffer, 4);

  //   printf("%d: got %s\n", child_pid, buffer);

  //   write(descriptors[1], "pong", 4);
  // }
  // else
  // {
  //   // parent
  //   int parent_pid = getpid();

  //   write(descriptors[1], "ping", 4);
    
  //   char buffer[10];

  //   read(descriptors[0], buffer, 4);

  //   printf("%d: got %s\n", parent_pid, buffer);
  // }

  exit(0);
}
