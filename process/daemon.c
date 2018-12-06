#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

/*
�����ػ�����ģ��
1.	�����ӽ��̣��������˳�
���й������ӽ����н�����ʽ�������˿����ն�
2.	���ӽ����д����»Ự
����	setsid()����
����	ʹ�ӽ�����ȫ�����������������
3.	�ı䵱ǰĿ¼Ϊ��Ŀ¼
����	chdir()����
����	��ֹռ�ÿ�ж�ص��ļ�ϵͳ
����	Ҳ���Ի�������·��
4.	�����ļ�Ȩ������
����	umask()����
����	��ֹ�̳е��ļ����������־ܾ�ĳЩȨ��
����	�����ػ����������
5.	�ر��ļ�������
����	�̳еĴ��ļ������õ����˷�ϵͳ��Դ���޷�ж��
6.	��ʼִ���ػ����̺��Ĺ���
7.	�ػ������˳���������ģ��	
*/

void daemonize(void)
{
    pid_t pid;
    /*
     * * ��Ϊһ���»Ự���׽��̣�ʧȥ�����ն�
     * */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    } else if (pid != 0) /* parent */
        exit(0);
    setsid();
    /*
     * * �ı䵱ǰ����Ŀ¼��/Ŀ¼��.
     * */
    if (chdir("/") < 0) {
        perror("chdir");
        exit(1);
    }
    /* ����umaskΪ0 */
    umask(0);
    /*
     * * �ض���0��1��2�ļ��������� /dev/null����Ϊ�Ѿ�ʧȥ�����նˣ��ٲ���0��1��2û������.
     * */
    close(0);
    open("/dev/null", O_RDWR);
    dup2(0, 1);
    dup2(0, 2);
}

int main(void)
{
    daemonize();
    while(1); /* �ڴ�ѭ���п���ʵ���ػ����̵ĺ��Ĺ��� */
}