#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int n = 5, i;				//Ĭ�ϴ���5���ӽ���

	if (argc == 2) {	
		n = atoi(argv[1]);
	}

	for (i = 0; i < n; i++)	//����1,������ר�ó���
		if (fork() == 0)
			break;			//����2,�ӽ��̳���,i������

	if (n == i) {
		sleep(n);
		printf("I am parent, pid = %d\n", getpid());
	} else {
		sleep(i);
		printf("I'm %dth child, pid = %d\n", 
				i+1, getpid());
	}

	return 0;
}
