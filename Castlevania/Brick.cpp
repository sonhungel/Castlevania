#include "Brick.h"

void CBrick::Render()
{
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (_width == 16)
	{
		left = x;
		top = y;
		right = x + 16;
		bottom = y + 16;
	}
	else
	{
		left = x;
		top = y;
		right = x + BRICK_WIDTH;
		bottom = y + BRICK_WIDTH;
	}
}