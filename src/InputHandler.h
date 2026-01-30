#ifndef INPUT_H
# define INPUT_H

# include "Allocator.h"
# include "Dynlist.h"
# include "Window.h"
# include "Vector.h"
# include <stdbool.h>

# define _INPUTHANDLER_CLEAR_BUFFER_ISIZE 16

typedef struct {
	const Window *win;
	Allocator *allocator;
	struct {
		Vec2 motion;
		Vec2 pos;
		Vec2 wheel;
		bool grabbed;
	} mouse;
	Dynlist *clear;
} InputHandler;

// al is nullable, malloc will be used instead
InputHandler inputhandler_create(Allocator *al, const Window *w);
// shall be called before event processing loop
void inputhandler_update(InputHandler *ih);
void inputhandler_processEvent(InputHandler *ih, const SDL_Event *ev);
void inputhandler_destroy(InputHandler *ih);

#endif // INPUT_H