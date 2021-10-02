#include <pthread.h>
#include <stdio.h>
int a = 0;
void* mythread1(void* dummy) {
  pthread_t mythID;
  mythID = pthread_self();
  a = a+1;
  printf("Thread %d, a = %d\n", mythID, a);
  return(NULL);
}
void* mythread2(void* dummy) {
  pthread_t mythID;
  mythID = pthread_self();
  a = a+1;
  printf("Thread %d, a = %d\n", mythID, a);
  return(NULL);
}
void main() {
  pthread_t thID1, thID2, mythID;
  int result;
  result = pthread_create(&thID1, (pthread_attr_t *)NULL, mythread1, NULL);
  if (result != 0) {
    printf("Error at thread create, returned value = %d\n", result);
    exit(-1);
  }
  printf("Thread created, thID = %d\n", thID1);
  result = pthread_create(&thID2, (pthread_attr_t *)NULL, mythread2, NULL);
  if (result != 0) {
    printf("Error at thread create, returned value = %d\n", result);
    exit(-1);
  }
  printf("Thread created, thID = %d\n", thID2);
  mythID = pthread_self();
  a = a+1;
  printf("Thread %d, a = %d\n", mythID, a);
  pthread_join(thID1, (void **) NULL);
  pthread_join(thID2, (void **) NULL);
}
/*
Thread 16386, a = 1
Thread created, thID = 16386
Thread 32771, a = 2
Thread created, thID = 32771
Thread 16384, a = 3
*/
