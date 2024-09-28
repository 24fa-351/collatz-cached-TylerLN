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

int main(int argc, char *argv[]) {
  if (argc != 6) {
    printf("Invalid/not enough inputs");
    return 1;
  }

  int user_n = atoi(argv[1]);
  int Min = atoi(argv[2]);
  int Max = atoi(argv[3]);
  char *cache_policy = argv[4];
  int cache_size = atoi(argv[5]);

  CachePolicy policy = CACHE_NONE;
  if (strcmp(cache_policy, "none") == 0) {
    policy = CACHE_NONE;
  } else if (strcmp(cache_policy, "LRU") == 0) {
    policy = CACHE_LRU;
  } else if (strcmp(cache_policy, "random") == 0) {
    policy = CACHE_RANDOM;
  }

  Cache *cache = initialize(cache_size);
  if (!cache) {
    return 1;
  }
  srand(time(NULL));
  int hitCount = 0;
  int totalRequests = 0;

  for (int ix = 0; ix < user_n; ix++) {
    int rand_num = rand() % (Max - Min + 1) + Min;
    unsigned long long int steps =
        collatz_cached(cache, rand_num, policy, &hitCount, &totalRequests);
    printf("%d, %llu steps\n", rand_num, steps);
  }
  printf("Hit Count: %d, Total Requests: %d\n", hitCount, totalRequests);

  double hitPercentage;
  if (totalRequests == 0) {
    hitPercentage = 0.0;
  } else {
    hitPercentage = (hitCount * 100.0 / totalRequests);
  }

  printf("Cache Hit Percentage: %.2f%%\n", hitPercentage);

  free(cache->entries);
  free(cache);

  return 0;
}
