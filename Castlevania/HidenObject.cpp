#include "HidenObject.h"

void CHidenObject::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + HIDENOBJECT_WIDTH;
	bottom = y + HIDENOBJECT_HEIGHT;
}

void CHidenObject::Render()
{
	RenderBoundingBox();
}
