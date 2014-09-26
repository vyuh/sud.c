#include <stdio.h>
#include <stdlib.h>

void die(char *msg){
    fputs(msg, stderr);
    exit(0);
}
// USAGE: #include "die.c" /* includes stdio.h and stdlib.h */
