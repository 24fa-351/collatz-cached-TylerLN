#include "collatz.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cache.h"

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

  CachePolicy policy = getPolicy(cache_policy);

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
