#include "ItemKnife.h"

void CItemKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;
	right = x + ITEM_KNIFE_WIDTH;
	bottom = y + ITEM_KNIFE_HEIGHT;
}
