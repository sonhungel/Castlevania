#include "ItemKnife.h"

void CItemKnife::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_KNIFE_WIDTH;
		bottom = y + ITEM_KNIFE_HEIGHT;
	}
}
