#include<fcntl.h>
#include<stdio.h>


char str[]="hello";
int main(int argc,char *argv[]){
	int fd;
	char buf[256];
	mknod("fifo",010777,0);
	if(argc==2)
	   fd=open("fifo",O_WRONLY);
	else
	   fd=open("fifo",O_RDONLY);
	for(int i=0;i<10;i++){
		  write(fd,str,6);
	   
		read(fd,buf,6);
		printf("%s",buf);
     }

printf("\n");
	return 0;
		
}
