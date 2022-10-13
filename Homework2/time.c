/**
 * Records the amount of time to run a command.
 * Uses shared memory. 
 * Name: Gavin Worley
 */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/mman.h>
int main(int argc, char *argv[])
{
    const char *name = "v1";
    const int SIZE = 24;
    struct timeval start;
    struct timeval end;
    struct timeval elapsed_time;
    pid_t pid;
    int shm_fd;
    char *ptr;
    if (argc == 1)
        return 0;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        printf("shared memory creation failed\n");
        return  -1;
    }
    ftruncate(shm_fd, SIZE);
    ptr = (char *)mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        printf("memory map failed\n");
        return -1;    
    }
    pid = fork();
    if (pid == 0)
    {
        // child
        if (gettimeofday(&start, NULL) != 0)
            return 0;
	printf("\nChild Start time = %ld sec, %ld microsec\n",start.tv_sec, 
start.tv_usec);
        // [FILL UP] write the starting time to shared memory
        
	memcpy(ptr, &start, sizeof(struct timeval));


        // [FILL UP] now execute the command

        execvp(argv[1], argv + 1);
        
        fprintf(stderr, "Error");
    }
    else { 
    //parent
        wait(NULL);
    
        if (gettimeofday(&end, NULL) != 0)
            return -1;
        printf("\nParent ending time = %ld sec, %ld microsec\n",end.tv_sec, 
end.tv_usec);
        
        // [FILL UP] read the starting time from shared memory
	
	memcpy(&start, ptr, sizeof(struct timeval));
        
        // [FILL UP] now determine elapsed time

	timersub(&end, &start, &elapsed_time);

	printf("Elapsed time: %ld.%06ld\n", elapsed_time.tv_sec, elapsed_time.tv_usec);

        shm_unlink(name);
    }
    return 0;
}