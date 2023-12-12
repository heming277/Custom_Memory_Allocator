// allocator.c

#include "allocator.h"
#include <pthread.h>
#include <stdbool.h>

void buffer_pool_init(BufferPool *bp) {
    pthread_mutex_init(&(bp->lock), NULL);
    for (int i = 0; i < POOL_SIZE; ++i) {
        bp->pool[i].is_free = true;
    }
}

void* buffer_allocate(BufferPool *bp) {
    pthread_mutex_lock(&(bp->lock));
    for (int i = 0; i < POOL_SIZE; ++i) {
        if (bp->pool[i].is_free) {
            bp->pool[i].is_free = false;
            pthread_mutex_unlock(&(bp->lock));
            return bp->pool[i].data;
        }
    }
    pthread_mutex_unlock(&(bp->lock));
    return NULL; // No buffers available
}

void buffer_deallocate(BufferPool *bp, void *buffer) {
    pthread_mutex_lock(&(bp->lock));
    for (int i = 0; i < POOL_SIZE; ++i) {
        if (bp->pool[i].data == buffer) {
            bp->pool[i].is_free = true;
            break;
        }
    }
    pthread_mutex_unlock(&(bp->lock));
}

void buffer_pool_destroy(BufferPool *bp) {
    pthread_mutex_destroy(&(bp->lock));
}