#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>

int main(void){

	void sigint_handler(int sig);
	int pipefds[2];

	if(signal(SIGINT, sigint_handler) == SIG_ERR){
		perror("signal");
		exit(1);
	}

	if(pipe(pipefds) == -1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	int number;
	int i, m = 0;
	int flag = 0;
	pid_t pid = fork();

	if(pid == 0){
		printf("\nEnter a number: ");
		scanf("%d", &number);
		write(pipefds[1], &number, sizeof(number));
	}
	else if(pid > 0){
		wait(NULL);
		printf("Checking for prime number...\n");
		read(pipefds[0], &number, sizeof(number));
	
		m = number / 2;
		for(i=2; i <= m; i++){
			if(number % i == 0){
				printf("%d is not a prime number \n", number);
				flag = 1;
				break;
			}
		}
		if(flag == 0){
			printf("%d is a prime number \n", number);
		}
	}
return EXIT_SUCCESS;
}

void sigint_handler(int sig)
{
	printf("This is a special signal handler for SIGINT\n");
}
