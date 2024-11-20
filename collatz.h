#ifndef COLLATZ_H
#define COLLATZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cache.h"

unsigned long long int collatz_steps(unsigned long long int num) {
  unsigned long long int steps = 0;
  while (num != 1) {
    if (num % 2 == 0) {
      num = num / 2;
    } else {
      num = 3 * num + 1;
    }
    steps++;
  }
  return steps;
}

unsigned long long int collatz_cached(Cache *cache, int key, Cache_Policy policy,
                                      int *hit_count, int *total_requests) {
  (*total_requests)++;
  Cache_Entry *entry = lookup(cache, key, policy);
  if (entry != NULL) {
    (*hit_count)++;
    return entry->data;
  }
  unsigned long long int steps = collatz_steps(key);
  insert(cache, key, steps, policy);

  return steps;
}

Cache_Policy get_policy(const char *policy) {
  if (strcmp(policy, "none") == 0) {
    return CACHE_NONE;
  } else if (strcmp(policy, "LRU") == 0) {
    return CACHE_LRU;
  } else if (strcmp(policy, "random") == 0) {
    return CACHE_RANDOM;
  }
  return CACHE_NONE;
}

#endif  