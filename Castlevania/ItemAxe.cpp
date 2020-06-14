#include "ItemAxe.h"

void CItemAxe::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_AXE_WIDTH;
		bottom = y + ITEM_AXE_HEIGHT;
	}
}
