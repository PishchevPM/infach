#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER 12345

int result = 0;
int counter = 0;

/* funtion - obrabot4ik signalov SIGUSR1, SIGUSR2, SIGINT */
void my_handler(int nsig) {

	if (nsig == SIGUSR1) {
		result = result | (1<<counter);
		counter++;
		signal(SIGUSR1, my_handler);
	} else if (nsig == SIGUSR2) {
		counter++;
		signal(SIGUSR2, my_handler);
	} else if (nsig == SIGINT) {
		printf("Result is %d\n", result);
		exit(0);
	}
}

int main(int argc, char *argv[])
{
	pid_t pid;
	int n = NUMBER, s, retval;

	/* porozhdaem process */
	switch (pid = fork()) {
	case 0:
	/* mi nahodimsa v porozhdennom processe, kotorii budet polu4at imformatiu ot porozhdauschego */

	/* vistavlyaem reatiu processa na SIGUSR1, SIGUSR2 и SIGINT*/
		(void)signal(SIGUSR1, my_handler);
		(void)signal(SIGUSR2, my_handler);
		(void)signal(SIGINT, my_handler);

	/* process zhdet pobitovoi pereda4i 4isla */
		printf("Child wait...\n");
		while (1);

	case -1:
	/* process sodat ne udalos */
		printf("Can't fork child\n");
		exit(-1);
		break;
	default:
	/* mi nahodimsa v porozhdauschem processe, kotorii budet peredavat inf-u porozhdennomu */
		while (n != 0) {
			if (n & 1) {
				s = SIGUSR1;
			} else {
				s = SIGUSR2;
			}

			retval = kill(pid, s);
			if (retval != 0) {
				printf("Cannot send signal to child\n");
				exit(-1);
			}

			n = n >> 1;
			usleep(10000);
		}

	/* Zavershaem porozhdennii process, otpravlyaem emu SIGINT*/
		retval = kill(pid, SIGINT);
		if (retval != 0) {
			printf("Cannot send signal to child\n");
			exit(-1);
		}
		printf("Parent exit\n");
	}

	return 0;
}
