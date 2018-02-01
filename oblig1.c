#include <stdio.h> /* printf */
#include <stdlib.h> /* exit */
#include <unistd.h> /* fork */
#include <sys/wait.h> /* waitpid */
#include <sys/types.h> /* pid_t */

void process(int number, int time) {
  printf("Prosess %d kjører\n", number);
  sleep(time);
  printf("Prosess %d kjørte i %d sekunder\n", number, time);
}

int main(void) {
  int p;
  int i;
  int j;
  int k;
  int l;
  int m;


//process 0 and 2
  p = fork();
  if (p == 0) {
    process(0,1);
    printf("%d\n",p );
    exit(0); 
  }

 i = fork();
  if (i == 0) {
    process(2,3);
    printf("%d\n",i );
    exit(0); 
  }


  // process 1 and 4
waitpid(p, NULL, 0);
  j = fork();
  if (j == 0) {
    process(4,3);
    printf("%d\n",j );
    exit(0); 
}
  k= fork();
  if (k == 0) {
    process(1,2);
    printf("%d\n",k );
    exit(0); 
}

//process 3
waitpid(i,NULL,0);
l=fork();
    
    if (l == 0) {
    process(3,2);
    printf("%d\n",l );
    exit(0); 


  }

//process5
waitpid(i,NULL,0);
  m=fork();
    if (m == 0) {
    process(5,3);
    printf("%d\n",l );
    exit(0); 


  }


 
return 0;

}
