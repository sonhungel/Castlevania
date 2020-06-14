#pragma once
#include "Item.h"

#define ITEM_CLOCK_ANI_ID	709

#define ITEM_CLOCK_WIDTH	35
#define ITEM_CLOCK_HEIGHT	27

class CItemClock :public CItem
{
public:
	CItemClock(float _x, float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_CLOCK_ANI_ID);
		type_Item = TYPE_ITEM_CLOCK;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

