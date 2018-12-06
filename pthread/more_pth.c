#include"my.h"

void *tfn(void *arg){
    
    int i;

    i = (long)arg;
    sleep(i);
    printf("I'm %ldth thread,thread_id is %lu\n",i+1,pthread_self());

    return NULL;
}

int main(int argc,char *argv[])
{
    int n=5;
    long i;
    pthread_t tid;

    if(argc == 2)
        n = atoi(argv[1]);
    
    for(i=0;i<n;i++){
        pthread_create(&tid,NULL,tfn,(void *)i);
    }
    sleep(n);

    printf("main thread_id is %lu\n",pthread_self());

    return 0;
}
