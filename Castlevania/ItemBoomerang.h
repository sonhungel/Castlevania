#pragma once
#include"Item.h"

#define ITEM_BOOMERANG_ANI_ID	715

#define ITEM_BOOMERANG_WIDTH	32
#define ITEM_BOOMERANG_HEIGHT	32

class CItemBoomerang : public CItem
{
public:
	CItemBoomerang(float _x,float _y) :CItem(_x, _y)
	{
		AddAnimation(ITEM_BOOMERANG_ANI_ID);
		type_Item = TYPE_ITEM_BOMMERANG;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

