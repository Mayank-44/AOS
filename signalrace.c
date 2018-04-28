#include <signal.h>
#include <stdlib.h>
static int i=0;
sigcatcher()
{
	printf("PID %d caught one %d\n", getpid(),i++);

	signal(SIGINT, sigcatcher());
}

main()
{
int ppid;
signal(75, sigcatcher());
if (fork()==0)
{
	sleep(10);
	ppid= getppid();
	for (;;)
	if (kill(ppid, 75)==-1)
	exit(0);
}
nice(10);
for (;;);
}
