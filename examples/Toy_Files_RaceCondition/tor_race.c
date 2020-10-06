#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include <string.h>

static void charattime(char *);

int main(void){

    pid_t pid;
    pid = fork();

    if(pid == 0){
        //INSIDE CHILD
        charattime("output from child\n");
    } else {
        //INSIDE PARENT
        charattime("output from parent\n");
    }

    exit(0);
}

static void charattime(char *str){
    char *ptr;
    int c;

    setbuf(stdout, NULL);
    /* set unbuffered */
    for(ptr = str; (c = *ptr++) != 0; )
        putc(c, stdout);
}