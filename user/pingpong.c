#include "kernel/types.h"
#include "user/user.h"
#define  READ_FOR_PIPE 0
#define WRITEN_FOR_PIPE 1

int main(int argc, char *argv[])
{
	int pipe_p2c[2];
	int pipe_c2p[2];

	int pid;
	char buf[100];
	memset(buf, 100, 0);

	pipe(pipe_p2c);
	pipe(pipe_c2p);

	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0) {
		close(pipe_p2c[WRITEN_FOR_PIPE]);
		close(pipe_c2p[READ_FOR_PIPE]);
		read(pipe_p2c[READ_FOR_PIPE], buf, 10);
		printf("%d: received ping\n %s\n", getpid(), buf);
		write(pipe_c2p[WRITEN_FOR_PIPE], "qqwertasdfg", 10);
		close(pipe_p2c[READ_FOR_PIPE]);
		close(pipe_c2p[WRITEN_FOR_PIPE]);
		exit(0);

	} else {
		close(pipe_p2c[READ_FOR_PIPE]);
		close(pipe_c2p[WRITEN_FOR_PIPE]);
		write(pipe_p2c[WRITEN_FOR_PIPE], "qwertyuias", 10);
		read(pipe_c2p[READ_FOR_PIPE], buf, 10);
		printf("%d: received pong\n %s\n", getpid(), buf);
		close(pipe_p2c[WRITEN_FOR_PIPE]);
		close(pipe_c2p[READ_FOR_PIPE]);
		exit(0);

	}

	exit(0);
}
