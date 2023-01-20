#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
	printf("sleep the argv[0]:%s  argv[1]:%s\n", argv[0], argv[1]);
	if(argc != 2) {
		fprintf(2, "from sleep argument error\n");
		exit(1);
	}
	
	int i = atoi(argv[1]);
	sleep(i);	

	exit(0);
}
