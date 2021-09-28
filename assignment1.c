#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
int main()
{
	pid_t pid_1, pid_2, pid_3, parent, parent_pid1, parent_pid2, parent_pid2_1, child_1, child_2, child_2_1;
	int status;

	pid_1 = fork();

	if (pid_1 > 0) {
		parent = getpid();
		printf("Parent (PID %d) created child_1 (PID %d)\n", parent, pid_1);
		printf("Parent (PID %d) is waiting for child_1 (PID %d) to complete before creating child_2\n", parent, pid_1);
		wait(NULL);
		pid_2 = fork();
		wait(NULL);
	}

	if (pid_2 > 0) {
		wait(NULL);
	}

	if (pid_1 == 0) {
		child_1 = getpid();
		parent_pid1 = getppid();
		printf("child_1 (PID %d) is calling an external program, external_program.out and leaving parent\n", child_1);
		char pid_string[20];
		sprintf(pid_string, "%d", child_1);
		char *conc_pid = pid_string;
		char *conc_str = " for child_1";
		char str[80];
		strcat(strcpy(str, conc_pid), conc_str);
		execl("./external_program.out", "./external_program.out", str, NULL);  		
	}

	if (pid_2 == 0) {
		child_2 = getpid();
		parent_pid2 = getppid();
		printf("Parent (PID %d) created child_2 (PID %d)\n", parent_pid2, child_2);
		pid_3 = fork();
		if (pid_3 > 0) {
			wait(NULL);
			printf("child_1 and child_2 are completed and parent process is terminating.\n");
		}
		if (pid_3 == 0) {
			child_2_1 = getpid();
			parent_pid2_1 = getppid();
			printf("child_2 (PID %d) created child_2.1 (PID %d)\n", parent_pid2_1, child_2_1); 
			printf("child_2.1 (PID %d) is calling an external program, external_program.out, and leaving child_2\n", child_2_1);
			char pid_string[20];
			sprintf(pid_string, "%d", child_2_1);
			char *conc_pid = pid_string;
			char *conc_str = " for child_2.1";
			char str[80];
			strcat(strcpy(str, conc_pid), conc_str);
			execl("./external_program.out", "./external_program.out", str, NULL);
		}
	}
}
