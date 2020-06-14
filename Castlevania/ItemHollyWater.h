#pragma once
#include "Item.h"

#define ITEM_HOLLYWATER_ANI_ID	713

#define ITEM_HOLLYWATTER_WIDTH 35
#define ITEM_HOLLYWATTER_HEIGHT 27

class CItemHollyWater :  public CItem
{
public:
	CItemHollyWater(float _x, float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_HOLLYWATER_ANI_ID);
		type_Item = TYPE_ITEM_HOLLYWATER;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

