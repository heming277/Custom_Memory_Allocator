// allocator.h

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <pthread.h>
#include <stddef.h>
#include <stdbool.h> 


#define BUFFER_SIZE 1024
#define POOL_SIZE 256

typedef struct Buffer {
    unsigned char data[BUFFER_SIZE];
    bool is_free;
} Buffer;

// Buffer pool
typedef struct BufferPool {
    Buffer pool[POOL_SIZE];
    pthread_mutex_t lock;
} BufferPool;


//API to call 

// Initializes the buffer pool.
void buffer_pool_init(BufferPool *bp);

// Allocates a buffer from the pool.
void* buffer_allocate(BufferPool *bp);

// Deallocates a buffer from the pool.
void buffer_deallocate(BufferPool *bp, void *buffer);

// Destroys the buffer pool.
void buffer_pool_destroy(BufferPool *bp);

#endif // ALLOCATOR_H