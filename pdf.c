#include<string.h>
char string[]="hello world";

main()
{
	
int count,i;
int to_par[2],to_chil[2];
char buf[256];
pipe(to_par);
int fd=creat("file.txt",0777);
pipe(to_chil);

if(fork()==0)
{
	close(0);
	dup(to_chil[0]);
	close(1);
	dup(to_par[1]);
	close(to_par[1]);
	close(to_chil[0]);
	close(to_par[0]);
	close(to_chil[1]);
	
	for(;;)
	{
		if((count=read(0,buf,sizeof(buf)))==0)
			exit(0);
		write(1,buf,count);
	}
}
close(1);
dup(to_chil[1]);
close(0);
dup(to_par[0]);
close(to_chil[1]);
close(to_par[0]);
close(to_chil[0]);
close(to_par[1]);

for(i=0;i<15;i++)
{
	write(1,string,strlen(string));
	
	count=read(0,buf,sizeof(buf));
	write(fd,buf,count);
}

}
