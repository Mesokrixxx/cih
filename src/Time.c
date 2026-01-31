#include "Time.h"
#include <SDL3/SDL_timer.h>

Time time_now(void) {
	static uint64_t freq;
	static uint64_t start;
	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t diff;

	if (!start)
		start = now;
	if (!freq)
		freq = SDL_GetPerformanceFrequency();
	diff = now - start;
	return SEC_TO_NS(diff / (double)freq);
}
