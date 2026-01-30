#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "Window.h"
#include "Idea.h"

#define IDEAS_DLIST_ISIZE 8

typedef struct {
	Window *win;
	InputHandler 
	Dynlist *ideas;
	bool running;
} State;

int main(void) {
	State st;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr,
			"Failed to init sdl3: %s\n", SDL_GetError());
		return 1;
	}
	st.win = window_create(NULL, vec2i_of2i(1080, 720), "C Idea Handler");
	if (!st.win)
		return 1;
	st.ideas = dynlist_create(sizeof(Idea), IDEAS_DLIST_ISIZE, idea_destroy);
	if (!st.ideas)
		return 1;
	st.running = true;
	while (st.running) {
		SDL_Event ev;

		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_EVENT_QUIT) {
				st.running = false;
			}
		}
	}
	window_destroy(st.win);
	SDL_Quit();
	return 0;
}
