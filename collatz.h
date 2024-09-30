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
                                      int *hit_count, int *total_requests) {
  (*total_requests)++;
  CacheEntry *entry = lookup(cache, key);
  if (entry != NULL) {
    entry->key_usage++;
    (*hit_count)++;
    return entry->data;
  }
  unsigned long long int steps = collatz_steps(key);
  insert(cache, key, steps, policy);
  return steps;
}

CachePolicy get_policy(const char *policy) {
  if (strcmp(policy, "none") == 0) {
    return CACHE_NONE;
  } else if (strcmp(policy, "LRU") == 0) {
    return CACHE_LRU;
  } else if (strcmp(policy, "random") == 0) {
    return CACHE_RANDOM;
  }
  return CACHE_NONE;
}

#endif  // COLLATZ_H