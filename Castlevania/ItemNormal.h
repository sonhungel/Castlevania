#pragma once
#include "Item.h"

#define ITEM_WIDTH	30
#define ITEM_HEIGHT	35
class CItemNormal :public CItem
{
public:
	CItemNormal(float _x, float _y, int _type, int _ani) :CItem(_x, _y)
	{
		type_Item = _type;
		AddAnimation(_ani);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

