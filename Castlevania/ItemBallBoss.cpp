#include "ItemBallBoss.h"

void CItemBallBoss::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state = STATE_ITEM_EXSIST)
	{
		left = x;
		top = y;
		right = x + ITEM_BALLBOSS_WIDTH;
		bottom = y + ITEM_BALLBOSS_HEIGHT;
	}
}
