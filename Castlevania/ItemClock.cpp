#include "ItemClock.h"

void CItemClock::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_CLOCK_WIDTH;
		bottom = y + ITEM_CLOCK_HEIGHT;
	}
}
