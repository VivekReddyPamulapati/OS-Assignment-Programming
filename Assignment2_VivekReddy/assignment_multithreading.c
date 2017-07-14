#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t mutex_1;

int counter;		//Counter is declared as a global variable which can be a shared resource for multiple threads

void *child1(void *arg)
{
        while(1){
                pthread_mutex_lock(&mutex_1);
		sleep(1);	
		if(counter > 25){
			pthread_mutex_unlock(&mutex_1); // This the chnage that has been done, unlocking the resources if they are locked after the given condition
			pthread_exit(NULL);
			}
		else
			counter++;
                pthread_mutex_unlock(&mutex_1);
		printf("Child1: counter=%d\n", counter);
        }
}


int main(void)
{
        pthread_t tid1;
	counter = 0;

        pthread_mutex_init(&mutex_1,NULL);
        pthread_create(&tid1,NULL,child1,NULL);
        do{
                pthread_mutex_lock(&mutex_1);
                sleep(1);
		counter++;
                pthread_mutex_unlock(&mutex_1);
		printf("Main: counter=%d\n", counter);

        }while(1);
        pthread_exit(0);
}
