#include "Actions.h"

void PaddleDown(Rectangle *r, float spd)
{
	if (r->y <= 0)
		r->y = 1;
	else if (r->y + r->height > GetScreenHeight())
		r->y = GetScreenHeight() - r->height;

	r->y += spd;
}