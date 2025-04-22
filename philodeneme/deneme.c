#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

//pthread_mutex_t kilit;

void *prnt(void *arg)
{
    int *y = (int *)arg;
	for (int i = 0; i < 10; i++)
	{
		y[0] = y[0] + 1;
        printf("%d\n", y[0]);
	}
	return NULL;
}
int main()
{
    pthread_t a,b;
    int x[0];
    x[0] = 3;
    //pthread_mutex_init(&kilit,NULL);

    pthread_create(&a,NULL,prnt,&x);
    pthread_create(&b,NULL,prnt,&x);

    pthread_join(a,NULL);
    pthread_join(b,NULL);
    
    //pthread_mutex_destroy(&kilit);
    //printf("program bitti,%d \n",sayac);
    return 0;
}

