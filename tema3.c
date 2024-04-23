#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<time.h>

int pid = 0;
int partvect[400], signr = 0, partnr = 0;

void sigusr1_handler(int);
void create_stat(int, int, int, int*);
void print_stat(int);
void alarm_handler(int);

int main(void) {
	int des1[2], des2[2];
	char ch = 'e', readch;
	time_t startTime = time(NULL);

	pipe(des1);
	pipe(des2);

	if (pid = fork()) {
		close(des1[0]);

		signal(SIGALRM, alarm_handler);
		alarm(1);

		while (difftime(time(NULL), startTime) < 7.00) {
			write(des1[1], &ch, sizeof(ch));
		}

		close(des1[1]);
		close(des2[1]);

		wait(NULL);
		print_stat(des2[0]);
		close(des2[0]);
	}
	else {
		int totalnr = 0;
		close(des1[1]);
		close(des2[0]);

		(void)signal(SIGUSR1, sigusr1_handler);

		while (read(des1[0], &readch, sizeof(readch)) > 0) {
			if (readch == 'e') {
				partnr++;
				totalnr++;
			}
		}
		partvect[signr] = partnr;

		close(des1[0]);
		create_stat(des2[1], totalnr, signr, partvect);
		close(des2[1]);
	}
	return EXIT_SUCCESS;
}

void sigusr1_handler(int sig) {
	partvect[signr] = partnr;
	partnr = 0;
	signr++;

	(void)signal(SIGUSR1, sigusr1_handler);
}

void create_stat(int dest, int totalnr, int signr, int* partvect) {
	char txtln[100];
	strcpy(txtln, "Statistica:\n");
	write(dest, &txtln, sizeof(txtln));

	snprintf(txtln, sizeof(txtln), "Nr. total de caractere citite = %d\n", totalnr);
	write(dest, &txtln, sizeof(txtln));

	for (int i = 1; i <= signr; i++) {
		snprintf(txtln, sizeof(txtln), "Nr. de caractere citite dupa semnalul SIGUSR1 cu numarul %d = %d\n", i, partvect[i]);
		write(dest, &txtln, sizeof(txtln));
	}
}

void print_stat(int source) {
	char txtln[100];
	while (read(source, &txtln, sizeof(txtln)) > 0) printf("%s", txtln);
}

void alarm_handler(int sig) {
	kill(pid, SIGUSR1);
	alarm(1);
}
