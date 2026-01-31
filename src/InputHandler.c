#include "InputHandler.h"
#include <stdio.h>

#define INPUTHANDLER_CLEAR_BUFFER_ISIZE 16

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
		.clear = dynlist_create(sizeof(unsigned int), INPUTHANDLER_CLEAR_BUFFER_ISIZE, NULL),
	};
	if (!ih->clear) {
		al ?
			allocator_free(al, sizeof(InputHandler))
			: free(ih);
		return NULL;
	}
	for (int i = 0; i < _INPUT_BUFFER_SIZE; i++)
		ih->input[i].state = INPUT_EXISTS;
	return ih;
}

void inputhandler_update(InputHandler *ih, Time now) {
	ih->now = now;
	ih->mouse.wheel = vec2_of(0, 0);
	ih->mouse.motion = vec2_of(0, 0);
	dynlist_foreach(ih->clear, idx, inputi,
		ih->input[*(unsigned int *)inputi].state &= ~(INPUT_PRESSED | INPUT_RELEASED);
	);
	dynlist_clear(ih->clear);
}

void inputhandler_processEvent(InputHandler *ih, const SDL_Event *ev) {
	unsigned int inputi;
	bool down, repeat;

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
					vec2_of(ev->wheel.x, ev->wheel.y));
			break ;
		case (SDL_EVENT_KEY_DOWN):
		case (SDL_EVENT_KEY_UP):
		case (SDL_EVENT_MOUSE_BUTTON_DOWN):
		case (SDL_EVENT_MOUSE_BUTTON_UP):
			if (ev->type == SDL_EVENT_KEY_DOWN 
					|| ev->type == SDL_EVENT_KEY_UP) {
				inputi = ev->key.scancode;
				down = ev->key.down;
				repeat = ev->key.repeat;
			} else {
				inputi = SDL_SCANCODE_COUNT + ev->button.button - 1;
				down = ev->button.down;
				repeat = false;
			}

			unsigned char cstate = ih->input[inputi].state;
			unsigned char nstate = INPUT_EXISTS;

			if (down) {
				if (!(cstate & INPUT_DOWN)) {
					nstate |= INPUT_PRESSED;
					dynlist_push(&ih->clear, &inputi);
				}
				nstate |= INPUT_DOWN;
				if (repeat)
					nstate |= INPUT_REPEAT;
			} 
			else {
				if (cstate & INPUT_DOWN) {
					nstate |= INPUT_RELEASED;
					dynlist_push(&ih->clear, &inputi);
				}
			}
			if ((nstate & INPUT_RELEASED) || (nstate & INPUT_PRESSED))
				ih->input[inputi].lastUpdate = ih->now;
			ih->input[inputi].state = nstate;
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

unsigned char inputhandler_state(const InputHandler *ih, unsigned int code) {
	if (code < 0 && code >= _INPUT_BUFFER_SIZE)
		return INPUT_INVALID;
	return ih->input[code].state;
}

Time inputhandler_lastUpdate(const InputHandler *ih, unsigned int code) {
	if (code < 0 && code >= _INPUT_BUFFER_SIZE)
		return 0;
	return ih->input[code].lastUpdate;
}
