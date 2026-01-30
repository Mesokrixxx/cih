#include "Window.h"
#include <stdio.h>

Window *window_create(Allocator *al, Vec2i size, const char *title) {
	Window *w;

	w = al 
		? allocator_alloc(al, sizeof(Window))
		: malloc(sizeof(Window));
	if (!w) {
		if (!al)
			perror("malloc");
		return NULL;
	}
	w->handler = 
		SDL_CreateWindow(
			title, size.x, size.y,
			SDL_WINDOW_RESIZABLE);
	if (!w->handler) {
		fprintf(stderr, 
			"Failed to create window handler: %s\n", 
			SDL_GetError());
		return NULL;
	}
	w->size = size;
	w->al = al;
	return w;
}

void window_destroy(Window *w) {
	if (!w)
		return ;
	SDL_DestroyWindow(w->handler);
	if (w->al) {
		// TODO handle this case, lowkey need to improve allocators tho
	}
	else
		free(w);
}
