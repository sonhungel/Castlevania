#pragma once
#pragma once
#ifndef __ITEM_WHIP_UPGRADE_H
#define __ITEM_WHIP_UPGRADE_H

#include"Item.h"
#include"Whip.h"

//==========DEFINE================

#define WHIPUPGRADE_WIDTH 38
#define WHIPUPGRADE_HEIGHT 38
class CItemWhipUpgrade :public CItem
{
public:
	CItemWhipUpgrade()
	{
		type_Item = TYPE_ITEM_WHIPUPGRADE;
		AddAnimation(700);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};
#endif

