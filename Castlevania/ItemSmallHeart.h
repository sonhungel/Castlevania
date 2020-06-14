#pragma once
#include "Item.h"

#define SMALLHEART_SPEED_X 0.2f
#define SMALLHEAR_GRAVITY	0.00015f

#define SMALLHEART_WIDTH	16
#define SMALLHEART_HEIGHT	16

#define ITEM_SMALLHEART_ANI_ID	704

class CItemSmallHeart :public CItem
{
private:
	float x_left;
	float x_right;
public:
	CItemSmallHeart(float _x = 0, float _y = 0) :CItem(_x, _y)
	{
		AddAnimation(ITEM_SMALLHEART_ANI_ID);
		type_Item = TYPE_ITEM_SMALLHEART;
		vx = SMALLHEART_SPEED_X;
		x_left = x - 20;
		x_right = x + 20;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

