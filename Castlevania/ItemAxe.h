#pragma once
#include "Item.h"

#define ITEM_AXE_ANI_ID		703

#define ITEM_AXE_WIDTH		32
#define	ITEM_AXE_HEIGHT		32

class CItemAxe :public CItem
{
public:
	CItemAxe(float _x = 0, float _y = 0):CItem(_x,_y)
	{
		type_Item = TYPE_ITEM_AXE;
		AddAnimation(ITEM_AXE_ANI_ID);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

