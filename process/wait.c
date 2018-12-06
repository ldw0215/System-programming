#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid, wpid;
	int status;

	pid = fork();

	if(pid == -1){
		perror("fork error");
		exit(1);
	} else if(pid == 0){		//son
		printf("I'm process child, pid = %d\n", getpid());
#if 1
		execl("./abnor", "abnor", NULL);
		perror("execl error");
		exit(1);
#endif
		sleep(1);				
		exit(10);
	} else {
		//wpid = wait(NULL);	//��������
		wpid = wait(&status);	//��������

		if(WIFEXITED(status)){	//�����˳�
			printf("I'm parent, The child process "
					"%d exit normally\n", wpid);
			printf("return value:%d\n", WEXITSTATUS(status));

		} else if (WIFSIGNALED(status)) {	//�쳣�˳�
			printf("The child process exit abnormally, "
					"killed by signal %d\n", WTERMSIG(status));
										//��ȡ�źű��
		} else {
			printf("other...\n");
		}
	}

	return 0;
}
