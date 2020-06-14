#include "ItemVase.h"

void CItemVase::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_VASE_WIDTH;
		bottom = y + ITEM_VASE_HEIGHT;
	}
}
