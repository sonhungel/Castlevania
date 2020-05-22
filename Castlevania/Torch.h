#pragma once
#ifndef __TORCH_H_
#define __TORCH_H_

#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"
#include"Item.h"
#include"ItemHeart.h"
#include"ItemWhipUpgrade.h"
#include"ItemKnife.h"
#include"Effect.h"


//===========DEFINE=======================
#define TORCH_WIDTH			32
#define TORCH_HEIGHT		68

#define STATE_TORCH_NOT_EXSIST		0
#define STATE_TORCH_EXSIST			1
#define STATE_TORCH_ITEM_EXSIST		2
#define STATE_TORCH_ITEM_NOT_EXSIST 3


#define ID_ITEM_WHIPUPGRADE			1
#define ID_ITEM_KNIFE				2
#define ID_ITEM_HEART				3
#define ID_ANIMATION_EFFECT		800

#define TIME_EFFECT		400	// thời gian bằng đúng số lượng frame animation* 100 mili seconds

class CTorch:public CGameObject
{
	DWORD dt_die; // đo thời gian cho animation lửa xuất hiện sau khi đánh stroke torch
	CItem* item;
	CEffect* effect;
	
public:
	CTorch(int id = 0); // id Item
	~CTorch()
	{
		CGameObject::~CGameObject();
		if (item != NULL)
			delete item;
	}
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetPosition(float _x, float _y) 
	{ 
		x = _x; 
		y = _y; 
		if (item != NULL)
			item->SetPosition(x+7, y);
	}
	CItem* GetItem() { return item; }
};
#endif
