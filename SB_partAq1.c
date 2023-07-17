#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

#define NUM_CHILDREN 3

// Function to handle the signal
void signal_handler(int signum) {
    printf("Receiving the signal %d. Exiting now...\n", signum);
    exit(0);
}

int main() {
    int pipe_fds[NUM_CHILDREN][2];
    for (int x = 0; x < NUM_CHILDREN; x++) {
        if (pipe(pipe_fds[x]) == -1) {
            perror("Pipe creation failed");
            return 1;
        }
    }

    int parent_id;
    int child_num;

    for (int x = 0; x < NUM_CHILDREN; x++) {
        parent_id = fork();
        if (parent_id == 0) {
            child_num = x + 1;
            break; // Child processes don't need to loop
        }
    }

    if (parent_id < 0) {
        perror("Fork has failed");
        return 1;
    } else if (parent_id == 0) {
        // Child process
        close(pipe_fds[child_num - 1][1]); // Close the write end of the pipe for the child

        char message[100];
        while (read(pipe_fds[child_num - 1][0], message, sizeof(message)) > 0) {
            printf("Child %d: Received message from parent: %s\n", child_num, message);
        }

        close(pipe_fds[child_num - 1][0]); // Close the read end of the pipe for the child
        printf("Child %d: Exiting...\n", child_num);
        exit(0);
    } else {
        // Parent process
        // Close unnecessary pipe ends for the parent
        for (int x = 0; x < NUM_CHILDREN; x++) {
            close(pipe_fds[x][0]); // Close the read end of the pipe for the parent
        }

        // Handle the signal
        signal(SIGINT, signal_handler);

        char *messages_to_children[NUM_CHILDREN] = {
            "Hello Child 1!",
            "Hello Child 2!",
            "Hello Child 3!"
        };

        for (int x = 0; x < NUM_CHILDREN; x++) {
            write(pipe_fds[x][1], messages_to_children[x], strlen(messages_to_children[x]) + 1); // +1 to include null terminator
        }

        // Close the write end of the pipe for the parent
        for (int x = 0; x < NUM_CHILDREN; x++) {
            close(pipe_fds[x][1]);
        }

        // Wait for child processes to finish
        for (int x = 0; x < NUM_CHILDREN; x++) {
            wait(NULL);
        }
    }

    return 0;
}