#pragma once
#include "Item.h"

//==========DEFINE=====================

#define KNIFE_WIDTH 38
#define KNIFE_HEIGHT 24

class CItemKnife :public CItem
{
public:
	CItemKnife()
	{
		type_Item = TYPE_ITEM_KNIFE;
		AddAnimation(702);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

