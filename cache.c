#include "cache.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Cache *initialize(int capacity) {
    Cache *cache = (Cache *)malloc(sizeof(Cache));
    if (cache == NULL)
        return NULL;

    cache->capacity      = capacity;
    cache->entries_count = 0;
    cache->entries       = (Cache_Entry *)calloc(capacity, sizeof(Cache_Entry));

    if (cache->entries == NULL) {
        free(cache);
        return NULL;
    }
    return cache;
}

Cache_Entry *lookup(Cache *cache, int key, Cache_Policy policy) {
    for (int ix = 0; ix < cache->entries_count; ix++) {
        if (cache->entries[ix].key == key) {
            if (policy == CACHE_MRU) {
                Cache_Entry accessed_entry = cache->entries[ix];
                for (int jx = ix; jx > 0; jx--)
                    cache->entries[jx] = cache->entries[jx - 1];
                cache->entries[0] = accessed_entry;
            }
            return &cache->entries[ix];
        }
    }
    return NULL;
}

void insert(Cache *cache, int key, int data, Cache_Policy policy) {
    for (int iy = 0; iy < cache->entries_count; iy++) {
        if (cache->entries[iy].key == key) {
            cache->entries[iy].data = data;
            lookup(cache, key, policy);
            return;
        }
    }

    if (cache->entries_count >= cache->capacity) {
        int evict_index = find_entry_to_evict(cache, policy);
        if (evict_index != -1)
            evict(cache, evict_index);
    }

    cache->entries[cache->entries_count].key  = key;
    cache->entries[cache->entries_count].data = data;
    cache->entries_count++;
}

int find_entry_to_evict(Cache *cache, Cache_Policy policy) {
    if (policy == CACHE_NONE)
        return -1;
    else if (policy == CACHE_LRU)
        return cache->entries_count - 1;
    else if (policy == CACHE_MRU)
        return 0;
    return -1;
}

void evict(Cache *cache, int entry_index) {
    for (int iz = entry_index; iz < cache->entries_count - 1; iz++)
        cache->entries[iz] = cache->entries[iz + 1];
    cache->entries_count--;
}
