#include "ItemWhipUpgrade.h"

void CItemWhipUpgrade::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + WHIPUPGRADE_WIDTH;
		bottom = y + WHIPUPGRADE_HEIGHT;
	}
}
