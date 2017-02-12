/* Example code for Think OS.
Copyright 2014 Allen Downey
License: GNU GPLv3
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "mutex.h"

#define NUM_CHILDREN 5

void perror_exit(char *s)
{
  perror(s);
  exit(-1);
}

void *check_malloc(int size)
{
  void *p = malloc(size);
  if (p == NULL) {
      perror_exit("malloc failed");
  }
  return p;
}

//struct containing values shared between threads
typedef struct {
  int counter;
} Shared;

//makes space for shared struct
//initializes struct contents
Shared *make_shared(int end)
{
  Shared *shared = check_malloc(sizeof(Shared));
  shared->counter = 0;
  return shared;
}

//pthread create wrapper
pthread_t make_thread(void *(*entry)(void *), Shared *shared)
{
  int ret;
  pthread_t thread;
  //creates and returns a pthread and returns 0 if unsuccessful
  ret = pthread_create(&thread, NULL, entry, (void *) shared);
  if (ret != 0) {
      perror_exit("pthread_create failed");
  }
  return thread;
}

void join_thread(pthread_t thread)
{
  //pthread_join wrapper, param = thread handle
  int ret = pthread_join(thread, NULL);
  // throws error for bad result
  if (ret == -1) {
      perror_exit("pthread_join failed");
  }
}

void child_code(Shared *shared)
{
  //prints counter value and increments it
  mutex_lock(shared->mutex);
  printf("counter = %d\n", shared->counter);
  shared->counter++;
  //unlocks mutex, allows next thread to go
  mutex_unlock(share->mutex)
}

void *entry(void *arg)
{
  //takes a void pointer that we assume is for
  //a Shared struct
  Shared *shared = (Shared *) arg;
  //calls child code with the new shared pointer
  child_code(shared);
  //gotta bounce
  pthread_exit(NULL);
}

int main()
{
  //NUM_CHILDREN compiles at runtime
  //child is array of thread handles
  int i;
  pthread_t child[NUM_CHILDREN];

  Shared *shared = make_shared(1000000);

  for (i=0; i<NUM_CHILDREN; i++) {
    child[i] = make_thread(entry, shared);
  }
  //joins each thread as it completes
  //don't need to end in order
  for (i=0; i<NUM_CHILDREN; i++) {
    join_thread(child[i]);
  }

  return 0;
}
