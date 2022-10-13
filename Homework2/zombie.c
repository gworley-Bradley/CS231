//Name: Gavin Worley
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>

int main()
{
pid_t id;

//fork system call returns child process id in parent process
id=fork();

// Parent process
if(id>0)
{
printf("Parent sleeping");
sleep(15);
}
//Child process
if(id==0)
{
printf("I am a child");
exit(0);
}
}