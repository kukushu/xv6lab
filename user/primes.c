#include "kernel/types.h"
#include "user/user.h" 


void child(int *pl) {
	int pr[2];
	int n;

	close(pl[1]);
	int read_result = read(pl[0], &n, sizeof(int));
	if (read_result == 0)
		exit(0);
	pipe(pr);
	if (fork() == 0) {
		child(pr);
	} else {
		close(pr[0]);
		printf("prime %d\n", n);
		int prime = n;
		while (read(pl[0], &n, sizeof(int)) != 0) {
			if (n % prime != 0 ) 
				write(pr[1], &n, sizeof(int));
		}
		close(pr[1]);
		wait((int *) 0);
		exit(0);
	}
}


int main(int argc, char *argv[])
{
	int p[2];
	pipe(p);
	if (fork() ==0) {
		child(p);
	} else {
		close(p[0]);
		for (int i = 2; i < 35 + 1; i ++) {
			write(p[1], &i, sizeof(int));
		}
		close(p[1]);
		wait((int *)0);
	}


	exit(0);
}
