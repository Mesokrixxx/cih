#ifndef ALLOCATOR_H
# define ALLOCATOR_H

# include <stdlib.h>

typedef struct {
	size_t size;
	size_t cap;
} Allocator;

Allocator *allocator_create(size_t size);
void *allocator_alloc(Allocator *allocator, size_t size);
void allocator_free(Allocator *allocator, size_t size);
void allocator_free_to(Allocator *allocator, size_t at);
void allocator_reset(Allocator *allocator);
void allocator_destroy(Allocator *allocator);

#endif // ALLOCATOR_H
