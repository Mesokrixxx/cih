#include "Input.h"
#include <SDL3/SDL_events.h>
#include <assert.h>

InputHandler *inputhandler_create(Allocator *al, const Window *w) {
	InputHandler *ih;

	ih = al ?
		allocator_alloc(al, sizeof(InputHandler))
		: malloc(sizeof(InputHandler));
	if (!ih) {
		if (!al)
			perror("inputhandler_create: malloc");
		return NULL;
	}
	*ih = (InputHandler){
		.win = w,
		.allocator = al,
		.clear = dynlist_create(sizeof(unsigned char), _INPUTHANDLER_CLEAR_BUFFER_ISIZE, NULL),
	};
	if (!ih->clear) {
		al ?
			allocator_free(al, sizeof(InputHandler))
			: free(ih);
		return NULL;
	}
	return ih;
}

void inputhandler_update(InputHandler *ih) {
	ih->mouse.wheel = vec2_of(0, 0);
	ih->mouse.motion = vec2_of(0, 0);
	dynlist_clear(ih);
}

void inputhandler_processEvent(InputHandler *ih, const SDL_Event *ev) {
	switch (ev->type) {
		case (SDL_EVENT_MOUSE_MOTION):
			ih->mouse.motion = 
				vec2_add(
					ih->mouse.motion,
					vec2_of(ev->motion.xrel, -ev->motion.yrel));
			ih->mouse.pos = 
				vec2_of(
					ev->motion.x,
					ih->win->size.y - ev->motion.y - 1);
			break ;
		case (SDL_EVENT_MOUSE_WHEEL):
			ih->mouse.wheel = 
				vec2_add(
					ih->mouse.wheel,
					vec2_of(ih->wheel.x, ih->wheel.y));
			break ;
		case (SDL_EVENT_KEY_DOWN):
		case (SDL_EVENT_KEY_UP):
		case (SDL_EVENT_MOUSE_BUTTON_DOWN):
		case (SDL_EVENT_MOUSE_BUTTON_UP):
			// TODO
			break ;
	}
}

void inputhandler_destroy(InputHandler *ih) {
	if (!ih)
		return ;
	dynlist_destroy(ih->clear);
	if (ih->allocator) {
		// TODO handle this (lowkey need to improve allocator tho ig)
	}
	else
		free(ih);
}

void 
