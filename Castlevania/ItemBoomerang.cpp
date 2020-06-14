#include "ItemBoomerang.h"

void CItemBoomerang::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_BOOMERANG_WIDTH;
		bottom = y + ITEM_BOOMERANG_HEIGHT;
	}
}
