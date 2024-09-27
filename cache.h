#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int key;       // key for cache entry
  int data;      // data with that key
  int keyUsage;  // how many times key has been used
} CacheEntry;    // tag for this struct

typedef struct {
  CacheEntry *entries;  // dynamic array of cache entries
  int capacity;
  int entriesCount;
} Cache;

typedef enum { CACHE_NONE, CACHE_LRU, CACHE_RANDOM } CachePolicy;

Cache *initialize(int capacity);  // initialize caceh with capacity
// Cache *cache is pointer to instance of Cache Structure
CacheEntry *lookup(Cache *cache,
                   int key);  // look up key, return what is in cache
void insert(Cache *cache, int key, int data);
int countofEntries(Cache *cache);

int findEntryToEvict(Cache *cache);
void evict(Cache *cache, int entryIndex);
void update(Cache *cache, int key, int newData);

#endif
