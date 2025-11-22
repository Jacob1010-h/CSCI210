#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

int main() {
    pid_t pid;
    char *argv[] = {"echo", "Hello from the spawned process!", NULL};
    int status;
    posix_spawnattr_t attr;

    // Initialize spawn attributes
    posix_spawnattr_init(&attr);

    // Set flags if needed, for example, to specify the scheduling policy
    // posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETSCHEDULER);

    // Spawn a new process
    if (posix_spawnp(&pid, "echo", NULL, &attr, argv, environ) != 0) {
        perror("spawn failed");
        exit(EXIT_FAILURE);
    }

    // Wait for the spawned process to terminate
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid failed");
        exit(EXIT_FAILURE);
    }

    if (WIFEXITED(status)) {
        printf("Spawned process exited with status %d\n", WEXITSTATUS(status));
    }

    // Destroy spawn attributes
    posix_spawnattr_destroy(&attr);

    return EXIT_SUCCESS;
}
