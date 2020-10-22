#include <stdio.h>
#include <stdlib.h>
#include <error.h>

static void charattime(char *);

/**
FINAL RESULTS:

race_condition.c:10:  [2] (race) vfork:
  On some old systems, vfork() permits race conditions, and it's very
  difficult to use correctly (CWE-362). Use fork() instead.
**/
int startProcess(char *strC, char *strP){
    
    pid_t pid;
    pid = vfork();

    if(pid == 0){
        //INSIDE CHILD
        charattime(strC);
    } else {
        //INSIDE PARENT
        charattime(strP);
    }
}

static void charattime(char *str){
    char *ptr;
    int c;

    setbuf(stdout, NULL);
    /* set unbuffered */
    for(ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);       
}