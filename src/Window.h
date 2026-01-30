#ifndef WINDOW_H
# define WINDOW_H

# include <SDL3/SDL_video.h>
# include "Allocator.h"
# include "Vector.h"

typedef struct {
	Allocator *al;
	SDL_Window *handler;
	Vec2i size;
} Window;

// allocator is nullable: will use malloc instead
Window *window_create(Allocator *al, Vec2i size, const char *title);
void window_destroy(Window *w);

#endif
