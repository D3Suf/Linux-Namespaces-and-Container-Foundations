#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mount.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SIZE (1024 * 1024)

// sync primitive
int checkpoint[2];

static char child_stack[STACK_SIZE];
char* const child_args[] = {
    "/bin/bash", NULL
};

// (needs root privileges (or appropriate capabilities))
int child_main(void* arg) {
    char c;

    // init sync primitive
    close(checkpoint[1]);

    // remount "proc" to get accurate "top" && "ps" output
    mount("proc", "/proc", "proc", 0, NULL);

    // wait ...
    read(checkpoint[0], &c, 1);

    printf(" - [%5d] World ! - child process prints its pid \n", getpid()); //  the child process prints its pid. It will always be "1" (from the perspective of the PID namespace of the child)!
    sethostname("In Namespace", 12);
    execv(child_args[0], child_args);
    printf("Ooops\n");
    return 1;
}

int main() {
    // init sync primitive
    pipe(checkpoint); // the parent process creates one unnamed pipe

    // parent process prints its pid
    printf(" - [%5d] Hello ? - parent pid \n", getpid());

    /**
    *   CLONE FLAGS:
    *   Váriaveis utilizadas para indicar as chamadas de sistemas (system calls)
    *   indicando o tipo de namespace a ser criado.
    *
    *   >   CLONE_NEWUTS : unix timesharing system namespace
    *   >   CLONE_NEWIPC : inter-process call namespace
    *   >   CLONE_NEWPID : process id namespace
    *   >   CLONE_NEWNS  : mount namespace
    */
    
    int child_pid = clone(child_main, child_stack+STACK_SIZE,
                             CLONE_NEWUTS | CLONE_NEWIPC | CLONE_NEWPID | CLONE_NEWNS | SIGCHLD,
                             NULL);

    // parent process prints the pid of the child.
    printf(" - Child process ID [%5d] - child pid from parent process print \n", child_pid);

    // some damn long init job
    sleep(4); // the parent process sleeps for 4 secounds
    // signal "done"
    close(checkpoint[1]); // the parent process closes the write end of the pipe, which will awake the child process.

    waitpid(child_pid, NULL, 0);
    return 0;
}