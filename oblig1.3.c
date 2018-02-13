#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include <unistd.h>     /* usleep */
#include <pthread.h>
#include <semaphore.h>
#define SHARED 0        /* process-sharing if !=0, thread-sharing if =0*/
#define BUF_SIZE 10
#define MAX_MOD 100000
#define NUM_ITER 200

void *Producer(void *); /* Producer thread */
void *Consumer(void *); /* Consumer thread */
int    validate (char *a); /*validates the input as an int*/
sem_t empty;            /* empty: How many empty buffer slots */
sem_t full;             /* full: How many full buffer slots */
sem_t b;                /* b: binary, used as a mutex */
int g_data[BUF_SIZE];   /* shared finite buffer  */
int g_idx;              /* index to next available slot in buffer, 
                           remember that globals are set to zero
                           according to C standard, so no init needed  */
struct threadargs {
        int id;         // Trådens ID
};
int main(void) {
  int i;
 char buffer[BUFSIZ];



   //Initialie the semaphores
   sem_init(&empty, SHARED, BUF_SIZE);
   sem_init(&full, SHARED, 0);
   sem_init(&b, SHARED, 1);


         printf("main started\n");
do { 
  
  printf ( "Enter a number: " );
  if ( fgets ( buffer, sizeof buffer, stdin ) != NULL ) {
    buffer[strlen ( buffer ) - 1] = '\0';
    if ( validate ( buffer ) == 0 ) {
      i = atoi ( buffer );
      printf ( "%d\n", i );
    }
    else
      printf ( "Error: Input validation\n" );
  }
  else
    printf ( "Error reading input\n" );
   
  }while(!i);  

pthread_t producers[i];
pthread_t consumers[i];
void *retvals[i];
struct threadargs* targs[i]; // Pekere til argumentene vi gir til trådene.
for(int h=0; h<i;h++){
targs[h] = malloc(sizeof(struct threadargs)); // Sett av minne, og
    targs[h]->id = 0;                             // sett alle variablene
  }

for (int k =0;k<i;k++){
targs[k]->id=k;
if(pthread_create(&producers[k], NULL, Producer, targs[k]) != 0)
        {
          fprintf(stderr, "error: Cannot create thread # %d\n", k);
          break;}
if (pthread_create(&consumers[k], NULL, Consumer, targs[k]) != 0)
        {
          fprintf(stderr, "error: Cannot create thread # %d\n", k);
          break;}

}

	// And wait for them to finish.
	for (int j = 0; j < i; j++)
    {
      if (pthread_join(consumers[j],&retvals[j]) != 0)
        {
          fprintf(stderr, "error: Cannot join thread # %d\n", j);
        }
if (pthread_join(producers[j],&retvals[j]) != 0)
        {
          fprintf(stderr, "error: Cannot join thread # %d\n", j);
        }
    }
	printf("main done\n");

	return 0;
}


void *Producer(void *arg) {
	int i=0, j;
struct threadargs *targs=arg;
	while(i < NUM_ITER) {
		// pretend to generate an item by a random wait
		usleep(rand()%MAX_MOD);
		
		// Wait for at least one empty slot
		sem_wait(&empty);
		// Wait for exclusive access to the buffer
		sem_wait(&b);
		
		// Check if there is content there already. If so, print a warning and exit.
		if(g_data[g_idx] == 1) { 
			printf("Producer overwrites!, idx er %d\n",g_idx); 
			exit(0); 
		}
		
		// Fill buffer with "data" (ie: 1) and increase the index.
		g_data[g_idx]=1;
		g_idx++;
		
		// Print buffer status.
		j=0; printf("(Producer %d, idx is %d): ",targs->id,g_idx);
		while(j < g_idx) { j++; printf("="); } printf("\n");
		
		// Leave region with exlusive access
		sem_post(&b);
		// Increase the counter of full bufferslots.
		sem_post(&full);
		
		i++;		
	}

	return 0;
}


void *Consumer(void *arg) {
	int i=0, j;
 struct threadargs *targs=arg;
	while(i < NUM_ITER) {
		// Wait a random amount of time, simulating consuming of an item.
		usleep(rand()%MAX_MOD);
		
		// Wait for at least one slot to be full
		sem_wait(&full);
		// Wait for exclusive access to the buffers
		sem_wait(&b);
		
		// Checkt that the buffer actually contains some data at the current slot.
		if(g_data[g_idx-1] == 0) { 
			printf("Consumes nothing!, idx er %d\n",g_idx);
			exit(0);
		}
		
		// Remove the data from the buffer (ie: Set it to 0) 
		g_data[g_idx-1]=0;
		g_idx--;
		
		// Print the current buffer status
		j=0; printf("(Consumer %d , idx is %d): ",targs->id,g_idx);
		while(j < g_idx) { j++; printf("="); } printf("\n");
		
		// Leave region with exclusive access
		sem_post(&b);
		// Increase the counter of empty slots.
		sem_post(&empty);  	

		i++;
	}

	return 0;

}

int validate ( char *a )
{
  unsigned x;
  for ( x = 0; x < strlen ( a ); x++ )
    if ( !isdigit ( a[x] ) ) return 1;
  return 0;
}
