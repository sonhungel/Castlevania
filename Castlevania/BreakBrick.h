#pragma once
#include "GameObject.h"
#include"EffectBrick.h"
#include"ItemMoney.h"
#include"ItemNormal.h"
#include"ItemSmallHeart.h"
#include"Define.h"
#include"HidenItem.h"


#define EFFECT_BRICK_ANI_ID  830

#define BREAK_BRICK_WIDTH		32
#define BREAK_BRICK_HEIGHT		32

#define BREAK_BRICK_EFFECT_TIME		2000

#define STATE_BREAK_BRICK_NOT_EXIST			0
#define STATE_BREAK_BRICK_EXIST				1
#define STATE_BREAK_BRICK_ITEM_EXIST		2
#define STATE_BREAK_BRICK_ITEM_NOT_EXIST	3


class CBreakBrick :public CGameObject
{
	vector<CEffectBrick*> listEffect;
	CItem* item;

	DWORD dt_effect;

public:

	CBreakBrick(float _x, float _y, int x_item, int y_item,int ani_id, int _typeitem=0)
	{
		type = eType::BREAK_BRICK;
		this->blood = 2;

		this->x = _x;
		this->y = _y;

		AddAnimation(ani_id);

		this->state = STATE_BREAK_BRICK_EXIST;

		for (UINT i = 0; i < 4; i++)
		{
			CEffectBrick *effect=new CEffectBrick(_x, _y, EFFECT_BRICK_ANI_ID, i);
			listEffect.push_back(effect);
		}
		// lưu ý chỉ cho những 
		if (_typeitem != 0)
		{
			if (_typeitem == eType::ITEM_HIDEN)
				item = new CHidenItem(x_item, y_item, x_item, y_item - HIDEN_ITEM_HEIGHT);
			else if (_typeitem == eType::ITEM_SMALLHEART)
			{
			}
			else if (_typeitem == eType::ITEM_RED_MONEY ||
				_typeitem == eType::ITEM_YELLOW_MONEY ||
				_typeitem == eType::ITEM_PURPLE_MONEY ||
				_typeitem == eType::ITEM_BLUE_MONEY)
			{
			}
			else
				item = new CItemNormal(x, y, _typeitem);
		}

		dt_effect = 0;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetState(int state)
	{
		CGameObject::SetState(state);
		if (state == STATE_BREAK_BRICK_ITEM_EXIST)
		{
			dt_effect = GetTickCount();
		}
	}
	CItem* GetItem() { return item; }
};

