#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "Window.h"
#include "InputHandler.h"
#include "Idea.h"

#define IDEAS_DLIST_ISIZE 8

typedef struct {
	Window *win;
	InputHandler *inputh;
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
	st.win = window_create(NULL, vec2i_of(1080, 720), "C Idea Handler");
	st.inputh = inputhandler_create(NULL, st.win);
	st.ideas = dynlist_create(sizeof(Idea), IDEAS_DLIST_ISIZE, (f_dynlist_free)idea_destroy);
	if (!st.win || !st.inputh || !st.ideas)
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
	SDL_Quit();
	return 0;
}
