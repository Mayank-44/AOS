#include <signal.h>
#include<stdio.h>
main()
{
extern catcher();
signal(SIGINT, catcher);
kill (0, SIGINT);
printf("process");
}
catcher()
{
printf("catcher");
}

