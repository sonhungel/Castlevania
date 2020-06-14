#pragma once
#include "Item.h"

#define ITEM_BALLBOSS_ANI_ID	714

#define ITEM_BALLBOSS_WIDTH 32
#define ITEM_BALLBOSS_HEIGHT 32

class CItemBallBoss : public CItem
{
public:
	CItemBallBoss(float _x, float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_BALLBOSS_ANI_ID);
		type_Item = TYPE_ITEM_BALL_BOSS;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

