#pragma once
#ifndef __ITEM_KNIFE_H_
#define __ITEM_KNIFE_H_

#include"Item.h"

//==========DEFINE=====================

#define ITEM_KNIFE_WIDTH 38
#define ITEM_KNIFE_HEIGHT 24

class CItemKnife :public CItem
{
public:
	CItemKnife()
	{
		type_Item = TYPE_ITEM_KNIFE;
		AddAnimation(701);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif

