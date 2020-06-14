#pragma once
#include "Item.h"

#define ITEM_III_ANI_ID	712

#define ITEM_III_WIDTH	35
#define ITEM_III_HEIGHT	27
class CItemIII :public CItem
{
public:
	CItemIII(float _x, float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_III_ANI_ID);
		type_Item = TYPE_ITEM_III;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

