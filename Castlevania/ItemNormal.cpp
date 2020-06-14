#include "ItemNormal.h"

void CItemNormal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_WIDTH;
		bottom = y + ITEM_HEIGHT;
	}
}
