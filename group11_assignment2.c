/* A PROGRAM THAT SEARCH AN ELEMENT IN AN ARRAY WHICH EXISTS IN A FILE 
1) FORK 2 CHILDREN IF SIZE OF THE ARRAY IS GREATER THAN 5 AND DIVIDE THE ARRAY BETWEEN THEM 
2) IF SIZE OF THE ARRAY IS LESS THAN OR EQUAL TO 5 IT WILL SEARCH THE ELEMENT .
3) IF ELEMENT FOUND  THEN THE PROCESS WILL WRITE THE INDEX OF THAT ELEMENT IN PIPE 
4) PARENT READ THE INDEX OF THE SEARCHED ELEMENT FROM THE PIPE AND PRINT ON CONSOLE.
5) IF ELEMENT NOT FOUND IT WILL PRINT "ELEMENT NOT FOUND" ON THE CONSOLE.


*********************************************************				*********************************************************************
																			SUBMITTED BY 
                                                        
                                                         		ANCHAL MITTAL
                                                        
                                                       					 MAYANK GANGWAR
***********************************************************************              ****************************************************
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int pfd[2];// AN ARRAY STORE THE PIPE RAED AND WRITE DESCRIPTOR
char ctype='p';//TYPE OF THE PROCESS
int array[1024];//USER SPACE WHERE THE FILE ARRAY COPY AFTER READING THE FILE
int count=0;
int size;//SIZE OF THE ARRAY

//============================FUNCTION THAT FORK THE PROCESS TO SEARCH AN ELEMENT IN AN ARRAY ==========================================

void fork_search(int array[], int search, int start, int end) {

	if ((end-start+1) <=5) {
	
		for(int i=start;i<=end;i++){
				
			if ((array[i]) == search) 
			    if(ctype=='c')			
                	write(pfd[1],&i,sizeof(i));
				else
					printf("ELEMENT FOUND AT INDEX: %d \n",i);
	    	}
	  
		}	
	
	
	else{
        pid_t child = fork();
      
      	  if (child == 0){
						ctype='c';
						close(pfd[0]);        	
						fork_search(array, search, start, (start+end)/2);
		}		
        else{
	       	pid_t child2 = fork();
      
       		 	if (child2 == 0){        
							ctype='c';
     						close(pfd[0]);	
							fork_search(array, search, (start + end)/2+1, end);
							}
        		}
    } 
}
//================================================FUNCTION THAT READ THE ARRAY FROM FILE===================================================


void read_data(char *str){
	FILE *myfile=fopen(str,"r");
	if(myfile==NULL){
		printf("ERROR WHILE OPENING THE FILE");
		exit(0);
	}
    while(fscanf(myfile,"%d,",&array[count++])!=EOF);
    size=count-1;
    fclose(myfile);
	
}


//==========================================================MAIN FUNCTION=================================================================

int main(int argc, char* argv[]){
if(argc!=3)
	exit(0);

//===========================================CREATING A UNAMED PIPE======================================================================

int ret_val = pipe(pfd);              

//==========================================IF ERROR OCCUR DURING PIPE CREATIONS===========================================================

if (ret_val != 0) {
	printf("ERROR OCCUR DURING CREATION OF FILE DUE TO ERROR NO ");
	exit(0);                  

}

//================================================READ THE ARRAY FROM THE FILE ============================================================

read_data(argv[1]);

//==========================CALL THE FUNCTION THAT FORK THE CHILD TO SEARCH AN ELEMENT======================================================

fork_search(array,atoi(argv[2]), 0, size-1);

//=====================================CLOSE THE WRITE DESCRIPTOR OF PIPE FOR PARENT=======================================================

close(pfd[1]); 

if(ctype=='p'){
	int d,j;
	j=read(pfd[0],&d,sizeof(d));
	if(j==0)
	printf("Element not found.\n");
	else
	printf("Element found at: %d \n",d);
   }

return 0;	
}
