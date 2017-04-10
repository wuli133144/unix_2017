#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "common.h"



int doit(int argc,char **argv){

    pid_t pid;
    pid=Fork();
    if(pid==0){//child proc todo it
         
          pid=Fork();
          if(pid>0){
             exit(0);// second parent exit
          }
      
            //child proc to do


            sleep(2);//abort parent proc
            printf("second child proc parent  id=%d\n ",getppid());
            exit(0);
     }

     if(waitpid(pid,NULL,0)!=pid){
         err_sys("waitpid error");
     }
    exit(0);

}

int main(int argc,char **argv){
    return doit(argc,argv);
}