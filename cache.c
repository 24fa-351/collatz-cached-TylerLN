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
  cache->entries_count = 0;
  cache->entries = (CacheEntry *)calloc(capacity, sizeof(CacheEntry));
  if (cache->entries == NULL) {
    free(cache);
    return NULL;
  }
  return cache;
}

CacheEntry *lookup(Cache *cache, int key) {
  for (int ix = 0; ix < cache->entries_count; ix++) {
    if (cache->entries[ix].key == key) {
      cache->entries[ix].key_usage++;
      return &cache->entries[ix];
    }
  }
  return NULL;
}

void insert(Cache *cache, int key, int data, CachePolicy policy) {
  if (cache->entries_count < cache->capacity) {
    cache->entries[cache->entries_count].key = key;
    cache->entries[cache->entries_count].data = data;
    cache->entries[cache->entries_count].key_usage = 0;
    cache->entries_count++;
  } else {
    int evict_index = find_entry_to_evict(cache, policy);
    evict(cache, evict_index);
    cache->entries[evict_index].key = key;
    cache->entries[evict_index].data = data;
    cache->entries[evict_index].key_usage = 0;
  }
}

int count_of_entries(Cache *cache) { return cache->entries_count; }

int find_entry_to_evict(Cache *cache, CachePolicy policy) {
  int evict_index = -1;

  if (policy == CACHE_NONE) {
    return -1;
  } else if (policy == CACHE_LRU) {
    int evict_index = 0;
    for (int iy = 1; iy < cache->entries_count; iy++) {
      if (cache->entries[iy].key_usage <
          cache->entries[evict_index].key_usage) {
        evict_index = iy;
      }
    }
  } else if (policy == CACHE_RANDOM) {
    srand(time(NULL));
    evict_index = rand() % cache->entries_count;
  }
  return evict_index;
}

void evict(Cache *cache, int entry_index) {
  cache->entries[entry_index].key = -1;
  cache->entries[entry_index].data = 0;
  cache->entries[entry_index].key_usage = 0;
  cache->entries_count--;
}

void update(Cache *cache, int key, int new_data) {
  for (int iz = 0; iz < cache->entries_count; iz++) {
    if (cache->entries[iz].key == key) {
      cache->entries[iz].data = new_data;
      cache->entries[iz].key_usage++;
      return;
    }
  }
}
