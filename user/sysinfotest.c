#include "kernel/types.h"
#include "kernel/sysinfo.h"
#include "user/user.h"

int
main()
{
  struct sysinfo info;
  if (sysinfo(&info) < 0) {
    printf("sysinfotest: sysinfo failed\n");
    exit(1);
  }

  printf("Free memory: %d bytes\n", info.freemem);
  printf("Processes: %d\n", info.nproc);
  printf("Open files: %d\n", info.nopenfiles);
  
  exit(0);
}
