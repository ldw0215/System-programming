/*��ִ��SIGINT�źŴ������ڼ�
 *����յ�SIGQUIT�źŶ���������(����)
 *SIGINT�źŴ����������꣬���̽����
 *SIGQUIT�źŵ����Σ�����û�в�׽���źţ�
 *������ִ�и��źŵ�Ĭ�϶����������˳�
 */
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void sig_int(int signo)
{
	printf("catch signal SIGINT\n");
	sleep(10);			//ģ���źŴ�����ִ�кܳ�ʱ��
	printf("end of handler\n");
}

int main(void)
{
	struct sigaction act;		


	act.sa_handler = sig_int;
	sigemptyset(&act.sa_mask);		
	sigaddset(&act.sa_mask, SIGQUIT);	

	/*��SIGQUIT�����ź����μ�,��͵���,�ڵ����źŴ������ڼ�
	 *��������ӦSIGINT�źű���,������ӦSIGQUIT*/
	act.sa_flags = 0;

	sigaction(SIGINT, &act, NULL);		//ע���ź�SIGINT��׽����

	while(1);

	return 0;
}
