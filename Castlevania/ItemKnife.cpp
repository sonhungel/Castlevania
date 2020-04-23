#include "ItemKnife.h"

void CItemKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + KNIFE_WIDTH;
	bottom = y + KNIFE_HEIGHT;
}
