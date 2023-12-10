#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#include <semaphore.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t mutex;
Zem_t phil;
Zem_t forks[22];
int n;
int array[22];


void getForks(int p)
{
   
    Zem_wait(&forks[p]);
    printf("philosopher %d picked up %d!\n", p, p);
    Zem_wait(&forks[(p+1)%n]);
    printf("philosopher %d picked up %d!\n", p, p+1);
    array[p] += 1;
  
 


}

void setForks(int p)
{
   
    Zem_post(&forks[p]);
    Zem_post(&forks[(p+1)%n]);
    printf("fork set down\n");
    Zem_post(&phil);
    


}

void *philosopher(void *arg) { 
    long long int value = (long long int) arg;
    int id = (int) value;
    printf("Philosopher started: %d\n",id);
    
    while(1)
    {
        
        
        Zem_wait(&phil);
        getForks(id);
        setForks(id);
        
        

       
    }
    printf("fail %d\n", id);
    return NULL;
}


int main(int argc, char *argv[]) {
    printf("Enter number of Philosophers: ");
    scanf("%d", &n);
    Zem_init(&mutex, 1);
    Zem_init(&phil,n-1);

    for (int i = 0; i < 22; ++i)
    {
        array[i] = 0;
    }

    for (int i = 0; i < n; ++i)
    {
        Zem_init(&forks[i], 1);
    
    }

    printf("Forks Initialized\n");

    for (int i = 0; i < n; ++i)
    {
        pthread_t c;
        long long int me = i;
        Pthread_create(&c, NULL, philosopher, (void *)me);
    }
    //mom(10);
 //    sem_wait(&s); // wait here for child
    int x = 0;
    while(1)
    {
    
     scanf("%d", &x);
     if (x == 1){
        printf(" start %d, %d, %d, %d, %d, %d ", array[0], array[1], array[2], array[3], array[4], array[5]);
        return 0;
     }
    }
   
}    
