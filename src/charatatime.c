
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "common.h"



static void printx(char *);

//some error happened 
//buffer errror
int doit(int argc,char **argv){

   pid_t pid;
   pid=Fork();
    switch (pid)
    {
        case 0:{//child proc
            WAIT_PARENT()//first run must be parent proc
            printx("output from child\n");
            break;
        }
        default:
            printx("output from parent\n");
            TELL_CHILD(pid);//active child proc
            break;
    }
    exit(0);

}


static void printx(char *str){
    char *ptr;
    char c;
    setbuf(stdout,NULL);//Set no buffer

    for(ptr=str;(c=*ptr++)!=0;)
    {
        putc(c,stdout);
    }

}

int main(int argc,char **argv){
    return doit(argc,argv);
}