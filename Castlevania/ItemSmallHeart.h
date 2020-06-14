#pragma once
#include "Item.h"

#define SMALLHEART_SPEED_X 0.03f
#define SMALLHEART_SPEED_Y	0.02f

#define SMALLHEART_WIDTH	16
#define SMALLHEART_HEIGHT	16

#define ITEM_SMALLHEART_ANI_ID	704

class CItemSmallHeart :public CItem
{
private:
	float x_left;
	float x_right;
public:
	CItemSmallHeart(float _x , float _y ) :CItem(_x, _y)
	{
		AddAnimation(ITEM_SMALLHEART_ANI_ID);
		type_Item = TYPE_ITEM_SMALLHEART;
		vx = SMALLHEART_SPEED_X;
		vy = SMALLHEART_SPEED_Y;
		x_left = _x - 15;
		x_right = _x + 15;
	}
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
};

