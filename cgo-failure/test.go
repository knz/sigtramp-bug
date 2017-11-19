package main

import (
  "fmt"
  "syscall"
)

// extern void test(void);
import "C"

func main() {
    fmt.Println("the text 'hello cont' should show below:")
    C.test();
    fmt.Println("no text should show now, and the program should terminate properly")
    syscall.Kill(syscall.Getpid(), syscall.SIGWINCH);
}