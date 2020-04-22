#include "ItemHeart.h"


void CItemHeart::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (STATE_ITEM_EXSIST)
	{
		left = x;
		right = x + HEART_WIDTH;
		top = y;
		bottom = y + HEART_HEIGHT;
	}
}
