#include <stdio.h> //Entering the header files 
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHMSIZE 1024
int main(void)
{


	key_t keyvalue;
	int shmid;
	int count;
	char *shm, *s;
	FILE * fptr;

	fptr = fopen("secrets.out","w"); //Creating secrects.out file to write the received data


	//SHARED MEMORY INITIALIZATION//
	
	keyvalue = getuid();		// We need to get the segment with keyvalue equal to the user ID, which was created by receiver.c
	
	shmid = shmget(keyvalue, SHMSIZE, 0666);		// Shared memory segment is located

	
	if (shmid < 0) 		// Error is raised if segment isn't located
		{
			perror("WARNING!!shared memory segment wasn't created");
			exit(EXIT_FAILURE);
		}

	
	shm = shmat(shmid, NULL, 0);	// Shared memory segment is attached to data space

	// Error is raised if segment isn't attached
	if (shm == (char *) -1) {
		perror("WARNING!!Could not attact shared memory segment");
		exit(EXIT_FAILURE);
	}
// This blocks gives the count of the total alpha numeric characters entered 
	for(;;) 
		{

		// Program waits until the user gives the input 
		if (*shm != '\0') {
				
				count = 0;
				for (s=shm; *s != '\0'; s++) {
					if (*s=='0'||*s=='1'||*s=='2'||*s=='3'||*s=='4'||*s=='5'||*s=='6'||*s=='7'||*s=='8'||*s=='9')
	    					{
                				count++;
            					}  
				}
				fptr = fopen("secrets.out","a");
				fprintf(fptr,"%s:%d\n",shm,count);
				fclose(fptr);
// This command of the program indicates that it has finished reading the input string by inserting an '\0' to the memory address shm is pointing to . Thus, receiver.c can ask the user for a new input and also, process.c is signalized to wait for the new input before writing it into the output file
				*shm = '\0';
				
			
		}
	}

	// The shared memory segment should be dettached from data space. An error is raised if segment isn't dettached
	if (shmdt(shm) == -1) {
		perror("WARNING!!Shared memory segment couldn't detach");
		exit(1);
	}
}
