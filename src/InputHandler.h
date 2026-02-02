#ifndef INPUT_H
# define INPUT_H

# include "Allocator.h"
# include "Dynlist.h"
# include "Window.h"
# include "Vector.h"
# include "Time.h"
# include <SDL3/SDL_events.h>
# include <SDL3/SDL_scancode.h>
# include <stdbool.h>

typedef enum {
	MOUSE_BUTTON_LEFT = SDL_SCANCODE_COUNT,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_SIDE0,
	MOUSE_BUTTON_SIDE1,
	_MOUSE_BUTTON_COUNT
} MouseButtonID;

# define _INPUT_BUFFER_SIZE (SDL_SCANCODE_COUNT + _MOUSE_BUTTON_COUNT)

# define INPUT_INVALID (0 << 0)
# define INPUT_PRESSED (1 << 0)
# define INPUT_RELEASED (1 << 1)
# define INPUT_DOWN (1 << 2)
# define INPUT_REPEAT (1 << 3)
# define INPUT_EXISTS (1 << 7)

typedef struct {
	const Window *win;
	Allocator *allocator;
	Time now;
	struct {
		Vec2 motion;
		Vec2 pos;
		Vec2 wheel;
		bool grabbed;
	} mouse;
	struct {
		unsigned char state;
		Time lastUpdate;
	} input[_INPUT_BUFFER_SIZE];
	Dynlist *clear;
} InputHandler;

// al is nullable, malloc will be used instead
InputHandler *inputhandler_create(Allocator *al, const Window *w);
// shall be called before event processing loop
void inputhandler_update(InputHandler *ih, Time now);
void inputhandler_processEvent(InputHandler *ih, const SDL_Event *ev);
void inputhandler_destroy(InputHandler *ih);

// Code must be an SDL_Scancode or a MouseButtonID
unsigned char inputhandler_state(const InputHandler *ih, unsigned int code);
// Code must be an SDL_Scancode or a MouseButtonID
Time inputhandler_lastUpdate(const InputHandler *ih, unsigned int code);

#endif // INPUT_H
