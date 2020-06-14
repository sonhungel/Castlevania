#pragma once
#ifndef __ITEM_HEART_H
#define __ITEM_HEART_H

#include"Item.h"

//=========DEFINE================
#define ITEM_HEART_ANI_ID	702

#define HEART_WIDTH 28
#define HEART_HEIGHT 25

class CItemHeart :public CItem
{
public:
	CItemHeart(float _x = 0, float _y = 0) :CItem(_x, _y)
	{
		type_Item = TYPE_ITEM_HEART;
		AddAnimation(ITEM_HEART_ANI_ID);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif

