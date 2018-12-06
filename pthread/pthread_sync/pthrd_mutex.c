#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/*
	同步方式：
	互斥量（互斥锁）pthread_mutex_ init
				   	destroy
				 	lock
					unlock
	读写锁：pthread_rwlock_
	条件变量：pthread_cond_		（重点：pthread_cond_wait）
	信号量：sem_ (互斥量的升级版)
		进程同步方式：1、信号量
					  2、文件锁
*/

pthread_mutex_t mutex;

void err_thread(int ret, char *str)
{
    if (ret != 0) {
        fprintf(stderr, "%s:%s\n", str, strerror(ret));
        pthread_exit(NULL);
    }
}

void *tfn(void *arg)
{
    srand(time(NULL));

    while (1) {

        pthread_mutex_lock(&mutex);
        printf("hello ");
        sleep(rand() % 3);	/*模拟长时间操作共享资源，导致cpu易主，产生与时间有关的错误*/
        printf("world\n");
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);

    }

    return NULL;
}

int main(void)
{
    int flag = 5;
    pthread_t tid;
    srand(time(NULL));

    pthread_mutex_init(&mutex, NULL);
    pthread_create(&tid, NULL, tfn, NULL);
    while (flag--) {

        pthread_mutex_lock(&mutex);

        printf("HELLO ");
        sleep(rand() % 3);
        printf("WORLD\n");
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);

    }
    pthread_cancel(tid);                //  将子线程杀死,子线程中自带取消点
    pthread_join(tid, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;                           //main中的return可以将整个进程退出
}

/*线程之间共享资源stdout*/
