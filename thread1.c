#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NUM_THREADS 5

/*
The first argument is a pointer to a pthread_t variable in which the thread id of the newly
created thread will be stored.

2- The second argument is a pointer to a thread attributes object. The attr object can be used to
set a thread attributes. Set to NULL for the default attributes.

3- The third argument is a pointer to the thread function (the subroutine the thread will be
executing).

4- The fourth argument is a pointer to a single argument variable that may be passed (by
reference) to the thread function. Set to NULL if no argument is passed.
*/

typedef struct args_struct{//struct being passed to the pthread function for creating a thread with two variables, array messages and int that holds the thread id number.
	char message[100];
	int thread_no;
}args_struct;

void *print_message(void *arguments){
	args_struct *args = (args_struct*) arguments; //assigns passed arguments to args.type casting needed as *arguments are void*.
	printf("<Message> %s from <Thread> #%d! with <ID> %ld\n", args->message, args->thread_no, pthread_self());
	pthread_exit(NULL); //necessary for exiting the thread safely.
}


int main(int argc,char *argv[]){
	pthread_t threads[NUM_THREADS];//array to hold all the thread ids.
	args_struct args_arr[NUM_THREADS]; // creating many iterations of the structs for every thread.

	char *message[] = {"RED", "GREEN", "BLUE", "YELLOW", "BLACk"};
	for(int i = 0; i < NUM_THREADS; i++){
		//Initialize the arugments struct for eac thread

		strcpy(args_arr[i].message, message[i]);
		args_arr[i].thread_no = i;

		printf("In main: creating thread #%d\n", i);
		pthread_create(&threads[i], NULL, print_message, &args_arr[i]); //creates the thread and in starts running the subroutine print_message
	}

	for(int i = 0; i < NUM_THREADS; i++){
		pthread_join(threads[i], NULL);
	}


	return 0;
}
