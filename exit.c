main()
{
	int child;
	if((child=fork())==0)
	{
		printf("child PID %d\n",getpid());
		pause();
	}
	printf("child PID %d\n",child);
	exit(child);
}
