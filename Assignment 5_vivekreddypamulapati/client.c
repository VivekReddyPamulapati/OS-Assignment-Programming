#include <stdio.h>
#include <rpc/rpc.h>
#include "os.h"
#include<string.h>
main(int argc, char ** argv)
{
    CLIENT * client;
    int * result;
    char * server;
    char * message;
	char input[256];

    if (argc != 2) {
	fprintf(stderr, "Usage : %s <host> <message>\n",argv[0]);
	exit(1);
    }
    server = argv[1];

for(;;)
	{//user input alpha numeric string
	printf(" Enter the alpha numeric string : ");
	fgets(input,BUFSIZ,stdin);
	message=input;
 
	client = clnt_create(server, ASSIGNMENT, ASSIGNMENTVERSION, "tcp");

  //error is shown if server doesn't connect 
    if (client == NULL) {
	clnt_pcreateerror(server);
	exit(1);
    }

   //calling the remote procedure
    result = myassignment_1(&message, client);
    if (result == (int *) NULL) {
	clnt_perror(client, server);//if server returns a NULL error msg is displayed
	exit(1);
    }
   //If the string input does not have the secret word C00L,if condition is executed,else the msg is stored in the secrets.out file
    if (*result == 0) {
	printf("WRONG TRY!!!!ENTER ALONG WITH SECRET CODE\n");
    }
	else{
 
    printf("Message delivered to %s\n",server);
   }
}
}


