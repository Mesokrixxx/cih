#ifndef VECTOR_H
# define VECTOR_H

typedef struct {
	int x;
	int y;
} Vec2i;

typedef struct {
	float x;
	float y;
} Vec2;

static inline Vec2i vec2i_of(int x, int y) {
	return (Vec2i){ x, y };
}

static inline Vec2 vec2_of(float x, float y) {
	return (Vec2){ x, y };
}

static inline Vec2 vec2_add(Vec2 v1, Vec2 v2) {
	return (Vec2){ v1.x + v2.x, v1.y + v2.y };
}

#endif
