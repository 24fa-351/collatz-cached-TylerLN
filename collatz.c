#include "collatz.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "cache.h"

int main(int argc, char *argv[]) {
  if (argc != 6) {
    printf("Inputs Invalid");
    return 1;
  }

  int userIteration = atoi(argv[1]);
  int Min = atoi(argv[2]);
  int Max = atoi(argv[3]);
  char *cachePolicy = argv[4];
  int cacheSize = atoi(argv[5]);

  CachePolicy policy = getPolicy(cachePolicy);

  Cache *cache = initialize(cacheSize);
  if (!cache) {
    return 1;
  }

  srand(time(NULL));
  int hitCount = 0;
  int totalRequests = 0;

  FILE *csv_file = fopen("Random_Percent.csv", "w");
  fprintf(csv_file, "user_iteration ,Min,Max, rand_num ,Steps\n");

  for (int ix = 0; ix < userIteration; ix++) {
    int randNum = rand() % (Max - Min + 1) + Min;
    unsigned long long int steps =
        collatz_cached(cache, randNum, policy, &hitCount, &totalRequests);
    printf("%d, %llu steps\n", randNum, steps);
    fprintf(csv_file, "%d,%d,%d,%d,%llu\n", userIteration, Min, Max, randNum,
            steps);
  }

  int hitMisses = totalRequests - hitCount;
  printf("Hit Count: %d, Hit Misesses: %d, Total Requests: %d\n", hitCount,
         hitMisses, totalRequests);

  double hitPercentage;
  if (totalRequests == 0) {
    hitPercentage = 0.0;
  } else {
    hitPercentage = (hitCount * 100.0 / totalRequests);
  }

  printf("Cache Hit Percentage: %.2f%%\n", hitPercentage);
  fclose(csv_file);

  free(cache->entries);
  free(cache);

  return 0;
}