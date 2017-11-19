#include <signal.h>
#include <string.h>
#include <assert.h>

// Note: this program can only be used on macOS/darwin.

void myhandler(int a) {}
void mytramp(void* a, int b, int c, siginfo_t* d, void* e) {}

int main(void) {
    struct __sigaction act, oact;
    memset(&act, 0, sizeof(act));
    memset(&oact, 0, sizeof(oact));

    act.sa_handler = myhandler;
    act.sa_tramp = mytramp;
    if (__sigaction(SIGCONT, &act, 0) == -1)
	perror("__sigaction");
    if (__sigaction(SIGCONT, 0, &oact) == -1)
	perror("__sigaction");

    assert(oact.sa_handler == myhandler);
    assert(oact.sa_tramp = mytramp);

    return 0;
}
