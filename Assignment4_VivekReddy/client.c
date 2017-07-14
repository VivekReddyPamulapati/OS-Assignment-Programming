/*Declaring the header files*/
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<errno.h>
#include	 <string.h>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<sys/socket.h>
#include	<netinet/in.h>
#include	<arpa/inet.h>
#include	<fcntl.h>


int main(int C, char *args[])
{

	int sd;
	char *check;
	struct sockaddr_in serveraddress;

	char *buffer = malloc(sizeof(char)*BUFSIZ);/*allocating memory for buffer dynamically*/
	
	if (C != 3)
        {

             printf("INVALID ARGUMENTS, ENTER THE IP ADDRESS OF THE SERVER YOU WISH TO CONNECT\n");
		printf("IN THIS FORMAT : x.x.x.x PortNo.\n");
		printf("The port configured for server is 5000%s\n", args[0]);
             exit(1);
        }
	/*Creating the socket*/
	sd = socket(AF_INET, SOCK_STREAM, 0);
	if(sd < 0)
    	{
		perror("!ERROR!");
		exit(1);
	}
	/*Configuring the server to connect to*/
    memset(&serveraddress, 0, sizeof serveraddress );
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_port = htons(atoi(args[2])); 		/* IP address is taken from the command line argument*/
    serveraddress.sin_addr.s_addr = inet_addr(args[1]); 	/*Get address from arguments*/
    
	/*connecting to the server*/
    if(connect(sd, (struct sockaddr*)&serveraddress, sizeof serveraddress ) < 0)
    {
        printf("Cannot Connect to server");
        exit(1);
    }
	else{
	printf("Connection successful\n");
	printf("TO disconnect from the server and close the connection, Type EXIT\n");	
	}
	
	for(;;) {
 	
	/*User is asked for an alpha numeric string input*/
	printf("Enter a alpha numeric along with the secret code ****: ");
	memset(buffer, 0, sizeof buffer );
	fgets(buffer, BUFSIZ, stdin);
        /*if the user wishes to close the server and client connection, EXIT command can be used to signal exit interrupt*/
        check = strstr (buffer,"EXIT");
        if (check!=NULL) {
            printf("The user has given exit command, closing server and client\n");
            if (send(sd, buffer, strlen(buffer), 0) < 0)	/*also sending the EXIT command to signal the server to close*/
                perror("send error:");
            exit(1);
        }
		check = strstr (buffer,"COOL");	
			if (check!=NULL) {
			
		if (send(sd, buffer, strlen(buffer), 0) < 0)
			perror("send error:");
			}
		}
	close(sd);
return 0;
}
