#include "Brick.h"

void CBrick::Render()
{
	if(animations.size()>0)
		animations[0]->Render(x, y);
	//else
		//RenderBoundingBox();
}

void CBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + BRICK_WIDTH;
	bottom = y + BRICK_WIDTH;
	
}