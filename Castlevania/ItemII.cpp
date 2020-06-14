#include "ItemII.h"

void CItemII::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_II_WIDTH;
		bottom = y + ITEM_II_HEIGHT;
	}
}
