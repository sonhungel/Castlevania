#pragma once
#include "Item.h"

#define ITEM_VASE_ANI_ID	716

#define ITEM_VASE_WIDTH 27
#define ITEM_VASE_HEIGHT 35

class CItemVase :public CItem
{
public:
	CItemVase(float _x, float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_VASE_ANI_ID);
		type_Item = TYPE_ITEM_VASE;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

