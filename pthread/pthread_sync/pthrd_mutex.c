#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

/*
	ͬ����ʽ��
	����������������pthread_mutex_ init
				   	destroy
				 	lock
					unlock
	��д����pthread_rwlock_
	����������pthread_cond_		���ص㣺pthread_cond_wait��
	�ź�����sem_ (��������������)
		����ͬ����ʽ��1���ź���
					  2���ļ���
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
        sleep(rand() % 3);	/*ģ�ⳤʱ�����������Դ������cpu������������ʱ���йصĴ���*/
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
    pthread_cancel(tid);                //  �����߳�ɱ��,���߳����Դ�ȡ����
    pthread_join(tid, NULL);

    pthread_mutex_destroy(&mutex);

    return 0;                           //main�е�return���Խ����������˳�
}

/*�߳�֮�乲����Դstdout*/
