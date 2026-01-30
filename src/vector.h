#ifndef VECTOR_H
# define VECTOR_H

typedef struct {
	int x;
	int y;
} Vec2i;

static inline Vec2i vec2i_of2i(int x, int y) {
	return (Vec2i){ x, y };
}

#endif
