#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int key;
  int data;
  int key_usage;
} CacheEntry;

typedef struct {
  CacheEntry *entries;
  int capacity;
  int entries_count;
} Cache;

typedef enum { CACHE_NONE, CACHE_LRU, CACHE_RANDOM } CachePolicy;

Cache *initialize(int capacity);
CacheEntry *lookup(Cache *cache, int key);
void insert(Cache *cache, int key, int data, CachePolicy policy);
int count_entries(Cache *cache);
int find_entry_to_evict(Cache *cache, CachePolicy policy);
void evict(Cache *cache, int entry_index);
void update(Cache *cache, int key, int new_data);

#endif  // CACHE_H
