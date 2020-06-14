#include "ItemHollyWater.h"

void CItemHollyWater::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_HOLLYWATTER_WIDTH;
		bottom = y + ITEM_HOLLYWATTER_HEIGHT;
	}
}
