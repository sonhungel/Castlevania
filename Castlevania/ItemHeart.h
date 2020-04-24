#pragma once
#ifndef __ITEM_HEART_H
#define __ITEM_HEART_H

#include"Item.h"

//=========DEFINE================

#define HEART_WIDTH 28
#define HEART_HEIGHT 25

class CItemHeart :public CItem
{
public:
	CItemHeart()
	{
		type_Item = TYPE_ITEM_HEART;
		AddAnimation(700);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif

