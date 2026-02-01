#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "Window.h"
#include "InputHandler.h"
#include "Idea.h"

#define IDEAS_DLIST_ISIZE 8

typedef struct {
	Allocator *g_allocator;
	Window *win;
	InputHandler *inputh;
	Dynlist *ideas;
	bool running;
} State;

int main(void) {
	State st;

	st.g_allocator = allocator_create(MiB(1));
	if (!st.g_allocator)
		return 1;
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr,
			"Failed to init sdl3: %s\n", SDL_GetError());
		return 1;
	}
	st.win = window_create(st.g_allocator, vec2i_of(1080, 720), "C Idea Handler");
	st.inputh = inputhandler_create(st.g_allocator, st.win);
	st.ideas = dynlist_create(sizeof(Idea), IDEAS_DLIST_ISIZE, (f_dynlist_free)idea_destroy);
	if (!st.ideas)
		return 1;
	st.running = true;
	while (st.running) {
		Time now = time_now();
		SDL_Event ev;

		inputhandler_update(st.inputh, now);
		while (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_EVENT_QUIT) {
				st.running = false;
			}
			window_processEvent(st.win, &ev);
			inputhandler_processEvent(st.inputh, &ev);
		}
	}
	dynlist_destroy(st.ideas);
	inputhandler_destroy(st.inputh);
	window_destroy(st.win);
	allocator_destroy(st.g_allocator);
	SDL_Quit();
	return 0;
}
