#pragma once
#pragma once
#ifndef __ITEM_WHIP_UPGRADE_H
#define __ITEM_WHIP_UPGRADE_H

#include"Item.h"
#include"Whip.h"

//==========DEFINE================

#define ITEM_WHIPUPGRADE_ANI_ID 700

#define WHIPUPGRADE_WIDTH 38
#define WHIPUPGRADE_HEIGHT 35
class CItemWhipUpgrade :public CItem
{
public:
	CItemWhipUpgrade(float _x = 0, float _y = 0):CItem(_x,_y)
	{
		type_Item = TYPE_ITEM_WHIPUPGRADE;
		AddAnimation(ITEM_WHIPUPGRADE_ANI_ID);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif

