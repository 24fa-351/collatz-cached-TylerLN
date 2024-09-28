#include "cache.h"

#include <stdio.h>
#include <stdlib.h>

Cache *initialize(int capacity) {
  Cache *cache = (Cache *)malloc(sizeof(Cache));
  if (!cache) {
    printf("Memory Allocation Failed\n");
    return NULL;
  }

  cache->entries = (CacheEntry *)malloc(sizeof(CacheEntry) * capacity);
  if (!cache->entries) {
    printf("Memory Allocation Failed\n");
    free(cache);
    return NULL;
  }

  cache->capacity = capacity;
  cache->entriesCount = 0;
  return cache;
}

CacheEntry *lookup(Cache *cache, int key) {
  for (int ix = 0; ix < cache->entriesCount; ix++) {
    if (cache->entries[ix].key == key) {
      cache->entries[ix].keyUsage++;
      return &cache->entries[ix];
    }
  }
  printf("Key %d not in cache\n", key);
  return NULL;
}

void insert(Cache *cache, int key, int data, CachePolicy policy) {
  if (cache->entriesCount < cache->capacity) {
    cache->entries[cache->entriesCount].key = key;
    cache->entries[cache->entriesCount].data = data;
    cache->entries[cache->entriesCount].keyUsage = 0;
    cache->entriesCount++;
    printf("Inserted key %d with data %d\n", key, data);
  } else {
    int evictIndex = findEntryToEvict(cache, policy);
    evict(cache, evictIndex);

    cache->entries[evictIndex].key = key;
    cache->entries[evictIndex].data = data;
    cache->entries[evictIndex].keyUsage = 0;
    printf("Inserted key %d with data %d after eviction\n", key, data);
  }
}

int count_of_entries(Cache *cache) { return cache->entriesCount; }

int findEntryToEvict(Cache *cache, CachePolicy policy) {
  int evictIndex = -1;

  if (policy == CACHE_NONE) {
    return -1;
  }

  if (policy == CACHE_LRU) {
    int minUsage = INT_MAX;
    for (int i = 0; i < cache->entriesCount; i++) {
      if (cache->entries[i].keyUsage < minUsage) {
        minUsage = cache->entries[i].keyUsage;
        evictIndex = i;
      }
    }
  }

  else if (policy == CACHE_RANDOM) {
    srand((unsigned int)time(NULL));
    evictIndex = rand() % cache->entriesCount;
  }

  return evictIndex;
}

void evict(Cache *cache, int entryIndex) {
  printf("Evicting key %d with data %d\n", cache->entries[entryIndex].key,
         cache->entries[entryIndex].data);

  cache->entries[entryIndex].key = -1;
  cache->entries[entryIndex].data = 0;
  cache->entries[entryIndex].keyUsage = 0;

  cache->entriesCount--;
}

void update(Cache *cache, int key, int newData) {
  for (int i = 0; i < cache->entriesCount; i++) {
    if (cache->entries[i].key == key) {
      cache->entries[i].data = newData;
      cache->entries[i].keyUsage++;
      printf("Updated key %d with new data %d\n", key, newData);
      return;
    }
  }
  printf("Key %d not found for update.\n", key);
}
