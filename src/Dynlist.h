#ifndef DYNLIST_H
# define DYNLIST_H

# include <stdlib.h>
# include <stdbool.h>

typedef void (*f_dynlist_free)(void *);

typedef struct {
	f_dynlist_free f_free;
	size_t data_size;
	size_t size;
	size_t cap;
} Dynlist;

Dynlist *dynlist_create(size_t data_size, size_t cap, f_dynlist_free f_free);
bool dynlist_push(Dynlist **dl, const void *val);
bool dynlist_pushs(Dynlist **dl, const void *val, size_t count);
void *dynlist_get(Dynlist *dl, size_t index);
void dynlist_clear(Dynlist *dl);
void dynlist_destroy(Dynlist *dl);

# define dynlist_foreach(_list, _it, _e, ...) \
	do { \
		for (size_t _it = 0; _it < (_list)->size; _it++) { \
			void *_e = dynlist_get((_list), _it); \
			__VA_ARGS__ \
		} \
	} while (0)

#endif // DYNLIST_H
