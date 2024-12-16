#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>  // Include this header for the wait() function

#define SHM_SIZE 1024  // Define the size of the shared memory

int main() {
    key_t key = ftok(".", 'x');  // Generate a unique key for shared memory
    if (key == -1) {
        perror("ftok failed");
        exit(1);
    }

    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    // Attach the shared memory to the process
    char *shmaddr = (char *)shmat(shmid, NULL, 0);
    if (shmaddr == (char *)-1) {
        perror("shmat failed");
        exit(1);
    }

    pid_t pid = fork();  // Create a child process

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {  // Child process
        // Write a message to shared memory
        printf("=Child %d begins\n", getpid());
        snprintf(shmaddr, SHM_SIZE, "Message from %d", getpid());
        printf("=Child %d ends\n", getpid());
        exit(0);
    } else {  // Parent process
        // Wait for child to finish
        wait(NULL);

        // Read the message from shared memory
        printf("=Parent %d begins\n", getpid());
        printf("%d gets %s\n", getpid(), shmaddr);
        printf("=Parent %d ends\n", getpid());

        // Detach the shared memory
        if (shmdt(shmaddr) == -1) {
            perror("shmdt failed");
            exit(1);
        }

        // Remove the shared memory segment
        if (shmctl(shmid, IPC_RMID, NULL) == -1) {
            perror("shmctl failed");
            exit(1);
        }
    }

    return 0;
}

