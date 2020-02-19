#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int NUM;
int N_threads;
int diff;
//int excess;
int* pr;

//function to identify prime numbers between a given range (low and high in this case)
void* prime(void* arg)
{
    int n = *((int*)arg);
    int low = (n-1)*diff+1; //calculating range for each thread. So, each thread operates over a splitted range of numbers.
    int high = n*diff;
    if(n==N_threads)
        high = NUM;     //if the split ins't equal, the last thread handles the excess numbers
    for(int i= low; i<=high; i++)
        {
            int flag = 0;
            for(int j = 2; j <= i/2; j++)
            {   //mark the non prime numbers
                if(i%j == 0)
                {
                    pr[i] = 1; //not prime
                    break;
                }
            }
        }
}

int main(int argc, char *argv[])
{
    if (argc!=3)
    {
        puts("usage: ./a.out <Max number> <No.of threads>");
        return 1;
    }
    NUM = atoi(argv[1]);
    N_threads = atoi(argv[2]); 
    int arr[NUM];
    pthread_t threads[N_threads];
    pr = calloc(NUM+1, sizeof(int));
    diff = NUM/N_threads;   //this is used to split the range of numbers for each thread
    int excess = NUM%N_threads;
    int i;
   if(N_threads>NUM)
       N_threads = excess;
    for(i=0; i<N_threads; i++)
    {
        arr[i] = i+1;
        pthread_create(&threads[i],NULL,&prime,&arr[i]); 
    }


    for(int j=0; j<N_threads; j++)
        pthread_join(threads[j],NULL);

    //once the thrad returns, print out the prime numbers
    i = 2;
    while(i<=NUM)
    {
        if(pr[i]!=1)
            printf("%d  ", i);   
        i++;
    }
    free(pr);
    return 0;
}
