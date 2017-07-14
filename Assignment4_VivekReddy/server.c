/*Include the header files required*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>
/*Defining the variable */
#define PORT 5000
#define BACKLOG 1

int lines=0,digitsum=0;

/*Function to count the number of digits in the string*/
int digits_in_str(char *s)
{
    int i = 0;
    while (*s != '\0') {
    	if (isdigit(*s))
       		i++;
    s++;
    }

    return i;
}

/*Handles the Ctrl-C interrupt and displays the summary*/
void my_handler(int s){
		printf("\nThe total number of lines received by the server is: %d \n",lines);
		printf("Total digit count across all input seen by the server is : %d \n ",digitsum);
        //   exit(1);

}


int main(int C, char *V[])
{
signal (SIGINT,my_handler);
int sock_fd, new_fd, buf_len, infinite_loop = 1,d;
	struct sockaddr_in serv_addr,client_addr;
	socklen_t sin_size;
	char s[100], buf[BUFSIZ],*check;
	
	FILE * fptr;

	fptr = fopen("secrets.out","w"); /*Creating secret.out file to write the received data*/
	fclose(fptr);

	sock_fd= socket(AF_INET,SOCK_STREAM,0);
	if(sock_fd<0){
		perror("Failed to create socket");
		exit(1);
		}

	/*This block initializing the server*/
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);


		// Error is raised if Bind Fails
		if (bind(sock_fd,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0) {
			close(sock_fd);
			perror("server: bind didn't work");
			exit(1);
		}


	

	/*this code facilitates the listening to the incoming sockets and waits for a connection, this is a blocking function*/
	if (listen(sock_fd, BACKLOG) < 0) {
		perror("listen: failed");
		exit(1);
	}
	printf("server: waiting for connections\n");
	
	sin_size = sizeof(client_addr);
		new_fd = accept(sock_fd, (struct sockaddr *)&client_addr, &sin_size);
		if (new_fd < 0) {
			perror("accept");
		}
printf("server: got connection from %s \n", inet_ntop(AF_INET, &client_addr.sin_addr, s, sizeof (s)));



	
	for(;;) 
		{	
		// error is raised if buffer is not received
		if ((buf_len = recv(new_fd, buf, BUFSIZ-1, 0)) < 0) 			{
			perror("recv: couldn't receive from client");
			exit(1);
		}

		/*The symbol '\0' to signalize the termination of the string.8?*/
		buf[buf_len] = '\0';
			
			check = strstr (buf,"EXIT");
			if (check!=NULL) {
				printf("The user has given exit command, closing the server");
			exit(1);}

		check = strstr (buf,"COOL");
			if (check!=NULL) {
			lines++;
		/*displaying the string received*/
		printf("server: string received %s \n",buf);
		
				fptr = fopen("secrets.out","a");
				d=digits_in_str(buf); /*calls the function to count the digits in the string*/
				digitsum=digitsum+d;	 /*this code sums the digits seen across the server*/
				fprintf(fptr, "%d: ", d);	
				fputs(buf, fptr);
				fclose(fptr);
			}	
			
		close(sock_fd);	/*The following command closes the socket.*/
	}

return 0;
	
}
