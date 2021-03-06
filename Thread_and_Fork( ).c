// Same thread id is printed in parent and child process.

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  . 
#include <pthread.h> 
 
void *myThread1(void *vargp) 
{ 
   int *myid = (int *)vargp;
    printf("Thread ID: %d\n", *myid); 
 
} 
 
void *myThread2(void *vargp) 
{ 
   int *myid = (int *)vargp;
    printf("Thread ID: %d\n", *myid); 
 
} 
 
int main() 
{ 
    pthread_t thread_1;
    pthread_t thread_2;
 
    printf(" Before Thread 1\n");
 
    pthread_create(&thread_1, NULL, myThread1, (void *)&thread_1);
    pthread_join(thread_1, NULL); 
 
    printf("After Thread 1\n"); 
 
    int pid = fork();
 
    if(pid==0)
    {
        printf(" In child process \n");   
        printf(" Before Thread 2 \n"); 
        printf("pid=%d ,parent=%d\n",getpid(),getppid());
     
        pthread_create(&thread_2, NULL, myThread2, (void *)&thread_2);
        pthread_join(thread_2, NULL); 
        printf("After Thread 2\n"); 
    }
    else{
        wait(NULL);
        printf(" In Parent process\n");
        printf(" Before Thread 2 \n"); 
        printf("pid=%d ,parent=%d\n",getpid(),getppid());
     
        pthread_create(&thread_2, NULL, myThread2, (void *)&thread_2);
        pthread_join(thread_2, NULL); 
        printf("After Thread 2\n"); 	
    }
 
 
    return 0; 
}
