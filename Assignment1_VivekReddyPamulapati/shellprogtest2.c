#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() // start of the shell command prompt
{

  char userCmdInput[50];

  puts("The program is a simple shell command prompt which when given the basic commands of a linux system like ls,date,mkdir,etc.. will execute their command properties!");
  for(;;)	// This is a infinite loop which won't terminate till it encounters a exit code zero;
    {
      printf("me@linux_user:~$");	//prompt for the command shell
      gets(userCmdInput);	//gets the users input
      if(strcmp(userCmdInput,"Exit")==0||strcmp(userCmdInput,"EXIT")==0||strcmp(userCmdInput,"exit")==0) //if the user enters a exit command the process stops and returns zero to the main process and comes out of the shell
      {
          return 0;
      }
      system(userCmdInput); // parses the user input to the system and creates a new child process that executes the command given by the user and returns the value to the parent process which is the main code of out program

    }
return 0;
}

// This is the other way implemetation of the Assignment question, here we directly call up a terminal and execute the require command, the cmdInput command tajes the input from the user and once the input is taken the string is compared in the condition and executed according to the condition ,other functionality of the command are explained in the code whereever required
