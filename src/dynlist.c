#include "dynlist.h"
#include <stdio.h>
#include <string.h>

Dynlist *dynlist_create(size_t data_size, size_t cap) {
	Dynlist *dl;

	dl = malloc(sizeof(Dynlist) + (data_size * cap));
	if (!dl) {
		perror("dynlist_create: malloc");
		return NULL;
	}
	*dl = (Dynlist){ .data_size = data_size, .cap = cap };
	return dl;
}

bool dynlist_push(Dynlist **dl, const void *val) {
	return dynlist_pushs(dl, val, 1);
}

bool dynlist_pushs(Dynlist **dl, const void *val, size_t count) {
	Dynlist *tmp = *dl;
	size_t nsize = tmp->size + count;

	if (nsize >= tmp->cap) {
		tmp = realloc(
			tmp, 
			sizeof(Dynlist) + (nsize * 2 * tmp->data_size));
		if (!tmp) {
			perror("dynlist_pushs: realloc");
			return false;
		}
		*dl = tmp;
	}
	memcpy(
		dynlist_get(tmp, tmp->size), 
		val, 
		tmp->data_size * count);
	return true;
}

void *dynlist_get(Dynlist *dl, size_t index) {
	return (char *)dl + sizeof(Dynlist) + (dl->data_size * index);
}

void dynlist_destroy(Dynlist *dl) {
	if (!dl)
		return ;
	free(dl);
}
