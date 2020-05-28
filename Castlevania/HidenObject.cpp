#include "HidenObject.h"

void CHidenObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CHidenObject::Render()
{
	RenderBoundingBox();
}
