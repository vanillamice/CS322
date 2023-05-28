#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>



#define NUM_SELLERS 4

enum bool{false = 0, true = 1};
typedef enum bool bool;

int tickets = 35;
int tot = 0;
sem_t s;

void *sell_tickets(void *arg){
    bool done = false;
    int ticketsSoldByThisThread = 0;
    int thread_no = (int) arg;

    while(!done){
        /* Random delay simulating some independent work done by the thread */
        sleep((rand() % 10) / 10);
        sem_wait(&s);
        /** Enter CRITICAL SECTION **/
        if(tickets == 0)done = true;
        else{
            tickets--;
            ticketsSoldByThisThread++;
            printf("Thread %d sold a ticket (%d tickets) (%d tickets left) %ld\n", thread_no, ticketsSoldByThisThread, tickets, pthread_self());
        }
        /** Exit CRITICAL SECTION **/
        sem_post(&s);
    }
    printf("All tickets sold! Thread %d sold %d tickets\n", thread_no, ticketsSoldByThisThread);
    tot += ticketsSoldByThisThread;
    return NULL;
}

int main(){

    srand(time(NULL));
    /* Initialize semaphore s */
    sem_init(&s, 0, 1);
    /* Main thread creates NUM_SELLERS threads */
    pthread_t t[NUM_SELLERS];
    int i;
    for(i=0; i<NUM_SELLERS; i++){
        printf("Main Thread: Creating Thread %d\n", i);
        pthread_create(&t[i], NULL, sell_tickets, (void*)i);
    }
    for(i=0; i<NUM_SELLERS; i++){
        pthread_join(t[i], NULL);
    }
    printf("Total: %d %d\n", tot, tickets);

return 0;
}
