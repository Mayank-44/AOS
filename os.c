/*A program that visits every directory starting with the current directory. It should be able to handle loops in the directory heirarchy. 
It read the directory and print the 
1: Owner
2: File type
3: Access Permissions
4: Access Time
*****************************************************************************************************************************************************************
                                               SUBMITTED BY
                                                     By ANCHAL MITTAL(Roll NO-4)
                                                                  and 
                                                     MAYANK GANGWAR(Roll No-16)
                                                     
*******************************************************************************************************************************************************************


*/
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>//format of directory entries
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include<pwd.h>

//**************************function that print the directory ,subdirectory and filepermission************************************
 
void printdir(char *dir, int depth){
    DIR *dp;//pointer to current directory
    struct passwd *pwd;
    
    struct dirent *entry;
    //********************user buffer statbuffer******************************************
    struct stat statbuf;
    //***********************space used for intention************************************
	int spaces = depth*4;
    //*****************open the current directory if NULL then return ********************************
    
    if((dp = opendir(dir)) == NULL) {
        
        fprintf(stderr,"***ERROR***  cannot open directory: %s\n", dir);
        return;
    }
   
    chdir(dir);// change directory to dir
  
    while((entry = readdir(dp)) != NULL) {
       
	        //used to extract information about the files and directories into user buffer(statbuffer)
                 stat(entry->d_name,&statbuf);
       
	        //ignore the current and parent directory
		if(strcmp(".",entry->d_name) == 0 ||strcmp("..",entry->d_name) == 0)
                continue;
       
	        //print the access permission 
                if(S_ISDIR(statbuf.st_mode)) {
           
                // ignore .(current) and ..(parent) directory 
            	if(strcmp(".",entry->d_name) == 0 ||  strcmp("..",entry->d_name) == 0)
               		 continue;
            
         	printf("%*s%s/\tDirectory ",spaces,"",entry->d_name);
            
	        printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
	        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
        	printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
        	printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
        	printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
        	printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
        	printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
        	printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
        	printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
        	printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
       
	      //print the size of the directory	
	        printf(" Size: %d bytes",statbuf.st_size);
	
	      //print the inode of the directory	
        //	printf(" inode: %d",statbuf.st_ino);
    
	      // if file type is directory
        	if (statbuf.st_mode & S_IFDIR)
        	        printf(" directory  ");
    
	      //if file type is charcter file 	        
        	if (statbuf.st_mode & S_IFCHR)
        	        printf(" chracter file  ");
    
	      //if file type is directory	        
        	if (statbuf.st_mode & S_IFREG)
        	        printf(" reggular file  ");
    
	      // get the owner id      
            	pwd = (getpwuid(statbuf.st_uid));
    
	      // error if owner id is NULL 
		if(pwd == NULL) 
		       perror("getpwuid");
            
	      // print the owner id
                else 
	              printf(" %s owner name ", pwd->pw_name);
            
	      // print the access time  of the directory  
                printf( " %s ",ctime(&statbuf.st_atime));
		printdir(entry->d_name,depth+1);
        
           }
        
        //if file
        else
	  {     
                printf("%*s%s\tFILE ",spaces,"",entry->d_name);
                printf( (S_ISDIR(statbuf.st_mode)) ? "d" : "-");
	        printf( (statbuf.st_mode & S_IRUSR) ? "r" : "-");
        	printf( (statbuf.st_mode & S_IWUSR) ? "w" : "-");
        	printf( (statbuf.st_mode & S_IXUSR) ? "x" : "-");
        	printf( (statbuf.st_mode & S_IRGRP) ? "r" : "-");
        	printf( (statbuf.st_mode & S_IWGRP) ? "w" : "-");
        	printf( (statbuf.st_mode & S_IXGRP) ? "x" : "-");
        	printf( (statbuf.st_mode & S_IROTH) ? "r" : "-");
        	printf( (statbuf.st_mode & S_IWOTH) ? "w" : "-");
        	printf( (statbuf.st_mode & S_IXOTH) ? "x" : "-");
               
	      //print the size of the file 	
	        printf(" Size: %d bytes",statbuf.st_size);
	
	      //print the inode of the file	
        //	printf(" inode: %d",statbuf.st_ino);
    
	      // get the owner id      
                pwd = (getpwuid(statbuf.st_uid));
    
	      // error if owner id is NULL 
	        if(pwd == NULL) 
		      perror("getpwuid");
            
	     // print the owner id of the file
                 else 
	              printf(" %s owner name ", pwd->pw_name);
            
	     // print the access time  of the file 
                 printf( " %s ",ctime(&statbuf.st_atime));
         
           }
    }
    
    //change directory tp parent directory
    chdir("..");
    
	//close the directory
    closedir(dp);

}

/* **************************************************** main function. ********************************************************** */

int main()
{
    char *topdir=".";//pointing to the current directory
   
    printf("Directory scan of %s\n",topdir);
    printdir(topdir,0);//calling the function that print the information of files and directory
    
	printf("***********Done************.\n");
    return 0;
}
