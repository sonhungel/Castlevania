#include "Brick.h"

void CBrick::Render()
{
	animations[0]->Render(x, y);
	//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_WIDTH;
	b = y + BRICK_WIDTH;
}