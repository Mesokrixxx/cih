#ifndef IDEA_H
# define IDEA_H

# include "Dynlist.h"

typedef struct {
	Dynlist *title;
	Dynlist *description;
} Idea;

Idea *idea_create(void);
void idea_destroy(Idea *idea);

#endif // IDEA_H
