#pragma once
#include "Item.h"

#define ITEM_KNIFE_ANI_ID			701
#define ITEM_WHIPUPGRADE_ANI_ID		700
#define ITEM_HEARTBIG_ANI_ID		702
#define ITEM_AXE_ANI_ID				703
#define ITEM_CLOCK_ANI_ID			709
#define ITEM_CROSS_ANI_ID			710
#define ITEM_II_ANI_ID				711
#define ITEM_III_ANI_ID				712
#define ITEM_HOLLYWATTER_ANI_ID		713
#define ITEM_BOSSBALL_ANI_ID		714
#define ITEM_BOOMERANG_ANI_ID		715
#define ITEM_VASE_ANI_ID			716
	

class CItemNormal :public CItem
{
	float width;
	float height;
public:
	CItemNormal(float _x, float _y, int _type) :CItem(_x, _y)
	{
		type = _type;
		LoadItem(_type);
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void LoadItem(int _type);
};

