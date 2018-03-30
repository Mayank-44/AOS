#include<signal.h>
main()
{

	register int i;
	setpgrp();
	for(i=0;i<10;i++)
	{
		if(fork()==0)
		{
			if(i&1)
			{	
				setpgrp();
				printf("i:%d ",i);
			}
			printf("pid=%d pgrp=%d\n",getpid(),getpgrp());
			pause();
		}
	}	
	kill(0,SIGINT);
}
