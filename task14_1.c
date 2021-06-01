#include <signal.h>
void main() {
	(void)signal(SIGQUIT,SIG_IGN);
	(void)signal(SIGINT,SIG_IGN);
	while(1);
}
