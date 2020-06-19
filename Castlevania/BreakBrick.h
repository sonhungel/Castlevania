#pragma once
#include "GameObject.h"
#include"EffectBrick.h"
#include"ItemMoney.h"
#include"ItemNormal.h"
#include"ItemSmallHeart.h"
#include"Define.h"


#define EFFECT_BRICK_ANI_ID  830

#define BREAK_BRICK_WIDTH		32
#define BREAK_BRICK_HEIGHT		32

#define BREAK_BRICK_TIME		2000


class CBreakBrick :public CGameObject
{
	vector<CEffectBrick*> listEffect;
	CItem* item;

public:
	bool isStroke;

	CBreakBrick(float _x, float _y,int ani_id)
	{
		type = eType::BREAK_BRICK;
		this->blood = 1;
		this->x = _x;
		this->y = _y;
		AddAnimation(ani_id);

		for (UINT i = 0; i < 4; i++)
		{
			CEffectBrick *effect=new CEffectBrick(_x, _y, EFFECT_BRICK_ANI_ID, i);
			listEffect.push_back(effect);
		}

		isStroke = false;
	}

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

