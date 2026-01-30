#ifndef DYNLIST_H
# define DYNLIST_H

# include <stdlib.h>
# include <stdbool.h>

typedef struct {
	size_t data_size;
	size_t size;
	size_t cap;
} Dynlist;

Dynlist *dynlist_create(size_t data_size, size_t cap);
bool dynlist_push(Dynlist **dl, const void *val);
bool dynlist_pushs(Dynlist **dl, const void *val, size_t count);
void *dynlist_get(Dynlist *dl, size_t index);
void dynlist_destroy(Dynlist *dl);

#endif
