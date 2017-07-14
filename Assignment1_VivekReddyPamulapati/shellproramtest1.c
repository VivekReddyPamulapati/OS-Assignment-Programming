/*Including the lbraries*/
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

int global;
int main()
{
    pid_t c_pid; //pid= Process Id
    int status;
    int local = 0;
    c_pid = fork(); // This where we create a new process 

if (c_pid >= 0) //giving the condition that if nw=ew created process is succesful
    {
        if (c_pid == 0)  /*Child Process and the process is giving the value 0*/
        {
          printf("child process!\n");
          local++;
          global++;
          printf("child PID is =  %d, parent PID is = %d\n", getpid(), getppid());
          printf("\n child's local value is = %d, child's global value is = %d\n",local,global); //printing the pid value of the child process 
	  printf("Enter any common aommands such as date,ls etc.. \n");
	  char *cmd[] = {"whoami",(char*)0};// calling the whoami command
          return execv("/usr/bin/",cmd);
        }

	else /* parent process */
        {
           printf("parent process!\n");
           printf("parent PID =  %d, child pid = %d\n", getpid(), c_pid);
           exit (0);
	}
        }

	else /* failure of the process creation */
       {
          perror("fork");
          exit(0);
       }
}

/*

fork(): "When fork(), the operating system will create a new process that is exactly the same as the parent process. This means all the state that was talked about previously is copied, including open files, register state and all memory allocations, which includes the program code.

The return value from the system call is the only way the process can determine if it was the existing process or a new one. The return value to the parent process will be the Process ID (PID) of the child, whilst the child will get a return value of 0.

At this point, we say the process has forked and we have the parent-child relationship"

exec(): "Forking provides a way for an existing process to start a new one, but what about the case where the new process is not part of the same program as parent process? This is the case in the shell; when a user starts a command it needs to run in a new process, but it is unrelated to the shell.

This is where the exec system call comes into play. exec will replace the contents of the currently running process with the information from a program binary.

Thus the process the shell follows when launching a new program is to firstly fork, creating a new process, and then exec (i.e. load into memory and execute) the program binary it is supposed to run."

