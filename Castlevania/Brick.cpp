#include "Brick.h"

void CBrick::Render()
{
	animations[0]->Render(x, y);
	RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BRICK_WIDTH;
	bottom = y + BRICK_WIDTH;
	
}