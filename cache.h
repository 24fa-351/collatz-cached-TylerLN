#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int key;
    int data;
} Cache_Entry;

typedef struct {
    Cache_Entry *entries;
    int capacity;
    int entries_count;
} Cache;

typedef enum { CACHE_NONE, CACHE_LRU, CACHE_MRU } Cache_Policy;

Cache *initialize(int capacity);
Cache_Entry *lookup(Cache *cache, int key, Cache_Policy policy);
void insert(Cache *cache, int key, int data, Cache_Policy policy);
int find_entry_to_evict(Cache *cache, Cache_Policy policy);
void evict(Cache *cache, int entry_index);

#endif
