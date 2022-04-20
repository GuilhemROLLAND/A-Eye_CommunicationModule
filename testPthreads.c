#include <pthread.h>
#include <stdio.h>

void* thread1() 
{
    printf("je suis dans le thread 1\n");
    return NULL;
}

void* thread2() 
{
    printf("je suis dans le thread 2\n");
    return NULL;
}

int main()
{
    pthread_t thr1;
    pthread_t thr2;

    pthread_create(&thr1, NULL, &thread1, NULL);
    printf("This line may be printed"
           " before thread terminates\n");
    
    pthread_join(thr1, NULL);
    printf("Thread 1 has ended\n");

    pthread_join(thr2, NULL);
    printf("Thread 2 has ended\n");

    printf("This line will be printed"
           " after thread ends\n");
  
    pthread_exit(NULL);
    return 1;
}