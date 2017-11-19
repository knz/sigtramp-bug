#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

// Note: this program can only be used on macOS/darwin.

void myhandler(int a) {
  write(2, "hello cont\n", 11);
}

// This is defined by libc, but not declared in the header signal.h.
// Declare it ourselves.
extern int __sigaction(int sig, const struct __sigaction *act, struct sigaction *oact);

void test(void* go_trampoline) {
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
    struct __sigaction newact;
    newact.sa_flags = oact.sa_flags;
    newact.sa_sigaction = oact.sa_sigaction;
    newact.sa_handler = oact.sa_handler;
    newact.sa_mask = oact.sa_mask;
    newact.sa_tramp = (void (*)(void*, int, int, siginfo_t*, void*))go_trampoline;
    if (__sigaction(SIGWINCH, &newact, 0) == -1)
	perror("__sigaction");
    

}
