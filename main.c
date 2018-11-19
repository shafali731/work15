#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/wait.h>
#include<unistd.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

int rand_num()
{
	int file = open("/dev/random", O_RDONLY);
	unsigned int rand;
	read(file, &rand, sizeof(int));
	if (errno)
	{
		printf("ERROR %d: %s\n", errno, strerror(errno));
	}
	close(file);
	return rand;
}

int main(){
  int f1;
  int f2;

  printf("From Parent before forking\n");
  if((f1 = fork())){
    if((f2 = fork())){
      printf("Parent pid: %d\n", getpid());
      int status;
      int c_pid = wait(&status);
      printf("Process %d slept for %d seconds. Parent is done\n", c_pid, WEXITSTATUS(status));
      return 0;
    }
  }
  printf("Child pid: %d \n", getpid());
  int sleep_time = rand_num()%15+5;
  sleep(sleep_time);
  printf("Child %d is done sleeping. It slept for %d seconds\n", getpid(), sleep_time);
  return 0;
}
