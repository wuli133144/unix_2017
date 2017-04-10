
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>


#include <sys/wait.h>


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

/*@pr_exit start@*/

void pr_exit(int status){
    if(WIFEXITED(status)){
        printf("normal termination ,exit status=%d\n",WEXITSTATUS(status));
    }
    else if(WIFSIGNALED(status)){
      printf("abnormal ternination ,signal,number=%d",WTERMSIG(status));
    }



}

/*@pr_exit end@*/


static int doit(int,char **);


int main(int argc,char **argv){
    return doit(argc,argv);
}





/*@doit  create by jackwu@*/



int doit(int argc,char **argv){
   
   pid_t pid;
   int status;
   if((pid=fork())<0){
     err_sys("fork error");
   }else if(pid==0){
     exit(7);
   }

   if(wait(&status)!=pid){
      err_sys("wait error");
   }
   pr_exit(status);
  

  /*@next @*/
if((pid=fork())<0){
     err_sys("fork error");
   }else if(pid==0){
    abort();
   }
   if(wait(&status)!=pid){
      err_sys("wait error");
   }
   pr_exit(status);

  
  exit(0);

}