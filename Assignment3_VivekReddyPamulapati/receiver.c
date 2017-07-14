#include <stdio.h>	/*Assinging the header files to the program */
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
	char *shm;
	char *user_input = malloc(sizeof(char)*BUFSIZ);
	char *check;


	// The key value is assigned by the getuid function which allocate the real value of the function call 
	keyvalue = getuid();

	// The shared memory segment is created
	shmid = shmget(keyvalue, SHMSIZE, IPC_CREAT | 0666);

	// Error is raised if segment isn't created
	if (shmid < 0) {
		perror("shmget function failed: shared memory was not created");
		exit(EXIT_FAILURE);
	}
	
	// Shared memory is attached to the data segments 
	shm = shmat(shmid, NULL, 0);

	// Error is raised if memory is not attached 
	if (shm == (char *) -1) {
		perror("shmat function failed: segment wasn't attached to data space");
		exit(EXIT_FAILURE);
	}


	for (;;) {

		//This loop accepts the  User is asked for an alpha numeric string input
		printf("Enter a string that has either COOL or not ");
		fgets(user_input, BUFSIZ, stdin);//gets the user input 
		check = strstr (user_input,"COOL");
			if (check!=NULL) {//continousy checking for the end of the file 
			strcpy(shm,user_input);
			}

			while(*shm!='\0') //This statement tells the receiver to wait until the processor has finished writing the output the string with secret code COOL and resumes asking the user for new input
				{
				sleep(1);
				}
		}

	}
