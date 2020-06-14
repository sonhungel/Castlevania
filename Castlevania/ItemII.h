#pragma once
#include "Item.h"

#define ITEM_II_ANI_ID	711

#define ITEM_II_WIDTH	35
#define ITEM_II_HEIGHT	27
class CItemII : public CItem
{
public:
	CItemII(float _x, float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_II_ANI_ID);
		type_Item = TYPE_ITEM_II;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

