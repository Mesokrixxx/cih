#ifndef IDEA_H
# define IDEA_H

# include "dynlist.h"

# define IDEA_TITLE_BUFFER_ISIZE 128
# define IDEA_DESCR_BUFFER_ISIZE 1028

typedef struct {
	Dynlist *title;
	Dynlist *description;
} Idea;

Idea *idea_create(void);
void idea_destroy(Idea *idea);

#endif // IDEA_H
