#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

pid_t fork(void);

int main() {
    pid_t pid = fork();

	if (pid == -1) {
		printf("Connection lost!\n");
	} else if (pid == 0) {
		printf("Child is coming.\n");
	} else {
		printf("Parent is coming.\n");
	}

	return 0;
}
