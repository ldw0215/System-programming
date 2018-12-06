#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

//fd[0] ���� fd[1] д��

int main(void)
{
	pid_t pid;
	int fd[2], i, n;
	char buf[1024];

	int ret = pipe(fd);
	if(ret == -1){
		perror("pipe error");
		exit(1);
	}

	for(i = 0; i < 2; i++){
		if((pid = fork()) == 0)
			break;
		else if(pid == -1){
			perror("pipe error");
			exit(1);
		}
	}

	if (i == 0) {			
		close(fd[0]);				
		write(fd[1], "1.hello\n", strlen("1.hello\n"));
	} else if(i == 1) {	
		close(fd[0]);				
		write(fd[1], "2.world\n", strlen("2.world\n"));
	} else {
		close(fd[1]);       //�����̹ر�д��,�����˶�ȡ����    
//		sleep(1);
		n = read(fd[0], buf, 1024);     //�ӹܵ��ж�����
		write(STDOUT_FILENO, buf, n);

		for(i = 0; i < 2; i++)		//��������wait����
			wait(NULL);
	}

	return 0;
}
