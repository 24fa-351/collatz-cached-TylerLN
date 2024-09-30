#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int key;
  int data;
} CacheEntry;

typedef struct {
  CacheEntry *entries;
  int capacity;
  int entries_count;
} Cache;

typedef enum { CACHE_NONE, CACHE_LRU, CACHE_RANDOM } CachePolicy;

Cache *initialize(int capacity);
CacheEntry *lookup(Cache *cache, int key, CachePolicy policy);
void insert(Cache *cache, int key, int data, CachePolicy policy);
int find_entry_to_evict(Cache *cache, CachePolicy policy);
void evict(Cache *cache, int entry_index);

#endif  // CACHE_H
