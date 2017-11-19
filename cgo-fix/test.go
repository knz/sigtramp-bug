package main

import (
  "fmt"
  "syscall"
  "github.com/knz/go-libedit/unix/sigtramp"
)

// extern void test(void*);
import "C"

func main() {
    fmt.Println("the text 'hello cont' should show below:")
    C.test(sigtramp.Get());
    fmt.Println("no text should show now, and the program should terminate properly")
    syscall.Kill(syscall.Getpid(), syscall.SIGWINCH);
}