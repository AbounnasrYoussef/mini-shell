#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler() {
    printf("Quit: 3");
}

int main() {
    signal(SIGQUIT, handler);
	sleep(100);
    signal(SIGQUIT, SIG_DFL);
	
    return 0;
}
