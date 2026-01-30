#include "Allocator.h"
#include <stdio.h>

Allocator *allocator_create(size_t size) {
	Allocator *al;

	al = malloc(sizeof(Allocator) + size);
	if (!al) {
		perror("allocator_create: malloc");
		return NULL;
	}
	*al = (Allocator){ .cap = size };
	return al;
}

void *allocator_alloc(Allocator *al, size_t size) {
	void *out;

	if (al->size + size >= al->cap) 
		return NULL;
	out = (char *)al + sizeof(Allocator) + al->size;
	al->size += size;
	return out;
}

void allocator_free(Allocator *al, size_t size) {
	al->size -= (size > al->size ? al->size : size);
}

void allocator_free_to(Allocator *al, size_t at) {
	al->size = (at > al->cap ? al->cap : at);
}

void allocator_reset(Allocator *al) {
	al->size = 0;
}

void allocator_destroy(Allocator *al) {
	if (!al)
		return ;
	free(al);
}
