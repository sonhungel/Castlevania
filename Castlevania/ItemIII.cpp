#include "ItemIII.h"

void CItemIII::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_III_WIDTH;
		bottom = y + ITEM_III_HEIGHT;
	}
}
