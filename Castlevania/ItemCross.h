#pragma once
#include "Item.h"

#define ITEM_CROSS_ANI_ID	710

#define ITEM_CROSS_WIDTH	35
#define ITEM_CROSS_HEIGHT	27

class CItemCross : public CItem
{
public:
	CItemCross(float _x, float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_CROSS_ANI_ID);
		type_Item = TYPE_ITEM_CROSS;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

