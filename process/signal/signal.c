#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

void do_sig(int a)
{
    printf("Hi, SIGALRM, how do you do !\n");
}

int main(void)
{
	alarm(5);
    if (signal(SIGALRM, do_sig) == SIG_ERR) {
        perror("signal");
        exit(1);
    }

    while (1) {
        printf("---------------------\n");
        sleep(1);
    }

    return 0;
}
