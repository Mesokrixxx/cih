#include "idea.h"
#include <stdlib.h>
#include <stdio.h>

Idea *idea_create(void) {
	Idea *i;

	i = malloc(sizeof(Idea));
	if (!i) {
		perror("idea_create: malloc");
		return NULL;
	}
	*i = (Idea) {
		.title = dynlist_create(sizeof(char), IDEA_TITLE_BUFFER_ISIZE),
		.description = dynlist_create(sizeof(char), IDEA_DESCR_BUFFER_ISIZE),
	};
	if (!i->title || !i->description) {
		idea_destroy(i);
		return NULL;
	}
	return i;
}

void idea_destroy(Idea *idea) {
	if (!idea)
		return ;
	dynlist_destroy(idea->title);
	dynlist_destroy(idea->description);
	free(idea);
}
