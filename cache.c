#include "cache.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Cache *initialize(int capacity) {
  Cache *cache = (Cache *)malloc(sizeof(Cache));
  if (cache == NULL) {
    return NULL;
  }
  cache->capacity = capacity;
  cache->entriesCount = 0;
  cache->entries = (CacheEntry *)calloc(capacity, sizeof(CacheEntry));
  if (cache->entries == NULL) {
    free(cache);
    return NULL;
  }
  return cache;
}

CacheEntry *lookup(Cache *cache, int key) {
  for (int ix = 0; ix < cache->entriesCount; ix++) {
    if (cache->entries[ix].key == key) {
      cache->entries[ix].keyUsage++;
      return &cache->entries[ix];
    }
  }
  return NULL;
}

void insert(Cache *cache, int key, int data, CachePolicy policy) {
  if (cache->entriesCount < cache->capacity) {
    cache->entries[cache->entriesCount].key = key;
    cache->entries[cache->entriesCount].data = data;
    cache->entries[cache->entriesCount].keyUsage = 0;
    cache->entriesCount++;
  } else {
    int evictIndex = findEntryToEvict(cache, policy);
    evict(cache, evictIndex);
    cache->entries[evictIndex].key = key;
    cache->entries[evictIndex].data = data;
    cache->entries[evictIndex].keyUsage = 0;
  }
}

int countOfEntries(Cache *cache) { return cache->entriesCount; }

int findEntryToEvict(Cache *cache, CachePolicy policy) {
  int evictIndex = -1;

  if (policy == CACHE_NONE) {
    return -1;
  } else if (policy == CACHE_LRU) {
    int evictIndex = 0;
    for (int ix = 1; ix < cache->entriesCount; ix++) {
      if (cache->entries[ix].keyUsage < cache->entries[evictIndex].keyUsage) {
        evictIndex = ix;
      }
    }
  } else if (policy == CACHE_RANDOM) {
    srand(time(NULL));
    evictIndex = rand() % cache->entriesCount;
  }
  return evictIndex;
}

void evict(Cache *cache, int entryIndex) {
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
      return;
    }
  }
}
