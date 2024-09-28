#ifndef COLLATZ_H
#define COLLATZ_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cache.h"

unsigned long long int collatz_steps(unsigned long long int n) {
  unsigned long long int steps = 0;
  while (n != 1) {
    if (n % 2 == 0) {
      n = n / 2;
    } else {
      n = 3 * n + 1;
    }
    steps++;
  }
  return steps;
}

unsigned long long int collatz_cached(Cache *cache, int key, CachePolicy policy,
                                      int *hitCount, int *totalRequests) {
  (*totalRequests)++;
  CacheEntry *entry = lookup(cache, key);
  if (entry != NULL) {
    entry->keyUsage++;
    (*hitCount)++;
    return entry->data;
  }
  unsigned long long int steps = collatz_steps(key);
  insert(cache, key, steps, policy);
  return steps;
}

CachePolicy getPolicy(const char *cache_policy) {
  if (strcmp(cache_policy, "none") == 0) {
    return CACHE_NONE;
  } else if (strcmp(cache_policy, "LRU") == 0) {
    return CACHE_LRU;
  } else if (strcmp(cache_policy, "random") == 0) {
    return CACHE_RANDOM;
  }
  return CACHE_NONE;
}

#endif