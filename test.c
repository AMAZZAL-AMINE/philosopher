#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *ft_routing() {
    
    while (1) {
        printf("routin turn\n");
        usleep(2);
    }
    return NULL;
}

void *tt(void *t) {
    int count = 0;
    while (count <= 910000000) {
       count++;
    }
    printf("final conunt result : %d\n", count);
    return NULL;
}

int main()
{
    pthread_t thread;
    pthread_create(&thread, NULL, tt, NULL);
    tt(NULL);
    pthread_join(thread, NULL);
    return 0;
}