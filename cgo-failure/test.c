#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

// Note: this program can only be used on macOS/darwin.

void myhandler(int a) {
  write(2, "hello cont\n", 11);
}

void test(void) {
    struct sigaction act, oact;

    // Save Go's handler.
    if (sigaction(SIGWINCH, 0, &oact) == -1)
	perror("sigaction");
    
    // Set our own handler.
    memset(&act, 0, sizeof(act));
    act.sa_handler = myhandler;
    act.sa_flags = SA_RESTART|SA_ONSTACK;
    if (sigaction(SIGWINCH, &act, 0) == -1)
	perror("sigaction");

    // Use our own handler.
    kill(getpid(), SIGWINCH);
    
    // Restore Go's handler.
    if (sigaction(SIGWINCH, &oact, 0) == -1)
	perror("sigaction");
    

}
