/**
 * HOW TO RUN
 * To compile: gcc -pthread -o sem sem.c
 * Run the program by: ./sem
 */

// include statements
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <semaphore.h>

// constants
#define ELEMENTS 100
#define NUM_PER_LINE 10

// global variable
int array_sum;
sem_t control; // semaphore


// function prototype
void *create_array(void*);
void sort(int[100]);
void print_array(int[100],int,int);

/*
/ Main function
*/
main(){
  
  sem_init(&control, 0, 1); // initializing semaphore

  pthread_t t1,t2,t3,t4; // 4 kerel threads
  
  pthread_create(&t1,NULL,create_array,(void*)"1");
  pthread_create(&t2,NULL,create_array,(void*)"2");
  pthread_create(&t3,NULL,create_array,(void*)"3");
  pthread_create(&t4,NULL,create_array,(void*)"4");
  pthread_join(t1,NULL);
  pthread_join(t2,NULL);
  pthread_join(t3,NULL);
  pthread_join(t4,NULL);
  printf("Total sum of the arrays: %d\n",array_sum);

  sem_destroy(&control); // destroy the semaphore
}

/*
 * Creates the 4 arrays woith random 100 generated numbers. It also calcultaes the sum of each thread and adds this to array_sum. 
 */
void *create_array(void *m){
  int num = atoi((char*) m); // convert the string passed to an integer
  int i=0;
  int array[ELEMENTS];
  int thread_sum = 0; 
  
  for (i;i<ELEMENTS;i++){
    array[i] = (rand()% 100) + (num*100);
    thread_sum += array[i]; //sum of one thread
  }  
  array_sum += thread_sum; // sum of all threads
  sem_wait(&control); // wait for the semaphore
  sort(array);
  print_array(array,num, thread_sum);
  sem_post(&control); 
}

/*
 * Prints the array to the monitor with 10 elements on each line. 
 * Also prints the sum of each thread after the thread has done printing.
 */
void print_array(int array[100],int num,int value){
  int i,j;
  j = 0; // next line checker

  for (i=0;i<ELEMENTS;i++){
    printf("%d ", array[i]);
    j++;
    if (j == NUM_PER_LINE){ // checks if 10 elements have been printed
      printf("\n");
      j=0;
    }
  }
  printf("\n");
  printf ("Sum of thread %d is: %d\n",num,value);
  printf("\n");
}

/*
 * Sorts the array in accending order 
*/
void sort(int array[100]){
  int temp = 0,i = 0,j = 0;

  for (i=0;i<ELEMENTS;i++){
    for (j=i+1;j<ELEMENTS;j++){
      if(array[j] < array[i]){
	temp = array[i];
	array[i] = array[j];
	array[j] = temp;
      
      }
    }
  }
}

