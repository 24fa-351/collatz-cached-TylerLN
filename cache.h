#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int key;
  int data;
  int keyUsage;
} CacheEntry;

typedef struct {
  CacheEntry *entries;
  int capacity;
  int entriesCount;
} Cache;

typedef enum { CACHE_NONE, CACHE_LRU, CACHE_RANDOM } CachePolicy;

Cache *initialize(int capacity);
CacheEntry *lookup(Cache *cache, int key);
void insert(Cache *cache, int key, int data, CachePolicy policy);
int countEntries(Cache *cache);
int findEntryToEvict(Cache *cache, CachePolicy policy);
void evict(Cache *cache, int entryIndex);
void update(Cache *cache, int key, int newData);

#endif
