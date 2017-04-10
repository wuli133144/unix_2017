
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

#include "err.h"


/*@err_exit() start@*/

#define err_exit(m) do{\
   perror(m);\
   exit(0);\
}while(0)
/*@err_exit() end@*/


/*@_error()@*/

#define __info(fmt,...)do{\
   printf("[%s]<%s> [%d]:",__FILE__,__func__,__LINE__);\
   printf(fmt,__VA_ARGS__);\
}while(0)


#define _pos()  __info("%s","\n")

#define mkstr(symbol)    #symbol

#define   _error(cond,err_table,fmt,...)         do{\
          if(cond){\
                __info("******error occured******|%s",mkstr(cond));  \
               printf(fmt,__VA_ARGS__);           \
               goto err_table;                    \ 
          }\
}while(0)

/*@_error() end@*/


/*@Fork start@*/
 
 pid_t Fork(){
   pid_t pid;
   if((pid=fork())<0){
     err_sys("%s error","fork");
   }
   return pid;
 }


/*@Fork end@*/


static int doit(int,char **);


int main(int argc,char **argv){
    return doit(argc,argv);
}





/*@doit  create by jackwu@*/

int g_val=6;
char buf[]="jackwu is number one";

int doit(int argc,char **argv){
   
   int var=88;
   pid_t pid;
      
    pid=Fork();
    if(pid==0){
      //child proc
      var++;
      g_val++;
    }else{
        sleep(2);
     }

  printf("pid=%d g_val=%d val=%d\n",getpid(),g_val,var);
  
 //_error(argc<2,doit_end,"%s","jackwu");

    return 0;
// doit_end:
//    exit(0);




}