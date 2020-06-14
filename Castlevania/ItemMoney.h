#pragma once
#include "Item.h"
#include"Effect.h"

#define ITEM_MONEY_WIDTH 32
#define ITEM_MONEY_HEIGHT 27

#define ITEM_MONEY_EFFECT_100	810
#define ITEM_MONEY_EFFECT_400	811
#define ITEM_MONEY_EFFECT_700	812
#define ITEM_MONEY_EFFECT_1000	813

class CItemMoney :public CItem
{
private:
	DWORD start_effection;
	CEffect* effect;

	float destination_x; // Dùng cho hiden money 1000
	float destination_y;

	bool isStartShowHiden;

public: 
	CItemMoney(float _x, float _y, int type, int ani_id) :CItem(_x, _y)
	{
		type_Item = type;
		AddAnimation(ani_id);
		switch (type)
		{
		case TYPE_ITEM_RED_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_100, x, y);
			break;
		case TYPE_ITEM_YELLOW_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_400, x, y);
			break;
		case TYPE_ITEM_PURPLE_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_700, x, y);
			break;
		case TYPE_ITEM_HIDEN_MONEY:
			effect = new CEffect(ITEM_MONEY_EFFECT_1000, x, y);
			break;
		default:
			break;
		}
	}
};

