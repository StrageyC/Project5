#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
//#include <semaphore.h>

#include "common.h"
#include "common_threads.h"
#include "zemaphore.h"

Zem_t mutex;
int flag;
Zem_t line;
Zem_t gate;
int servings;

void *passanger(void *arg) { 
    long long int value = (long long int) arg;
    int id = (int) value;
    while(1)
    {
        
        if (flag == 1 || line.value < 30){
            
            Zem_wait(&gate);
        } 
        Zem_wait(&line);

        printf("passanger %d is on bus!\n",id);

    
        return 0;
       
    }
   
    return NULL;
}

void *bus()
{
    while(1)
    {
        int val = line.value;
        int gal = gate.value;
        if (val == 0){
            sleep(2);
        }
        if (val < 30 )
        {
            
            flag = 1;
            for(int i = 0; i < val; ++i){

                Zem_post(&line);

            }
            
            Zem_post(&line);

            printf("bus left");

            for(int i = 0; i < val; ++i){

                if (gal < 0){
                    Zem_post(&gate);
                }
            }
            flag = 0;
            sleep(2);

        
        }
       
    }
}

int main(int argc, char *argv[]) {
    Zem_init(&mutex, 1);
    Zem_init(&line,0);
    Zem_init(&gate,0);

    int x = 1;
    pthread_t c;
    long long int me = x;
    Pthread_create(&c, NULL, bus, (void *)me);
    int i;
    while(1)
    {
        i++;
        pthread_t c;
        long long int me = i;
        sleep(2);
        Pthread_create(&c, NULL, passanger, (void *)me);
    }
   
//    sem_wait(&s); // wait here for child
    printf("parent: end\n");
    return 0;
}
    
