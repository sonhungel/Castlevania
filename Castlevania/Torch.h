#pragma once
#ifndef __TORCH_H_
#define __TORCH_H_

#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"
#include"Item.h"
#include"ItemNormal.h"
#include"Effect.h"


//===========DEFINE=======================
#define TORCH_WIDTH			32
#define TORCH_HEIGHT		68

#define STATE_TORCH_NOT_EXIST		0
#define STATE_TORCH_EXIST			1
#define STATE_TORCH_ITEM_EXIST		2
#define STATE_TORCH_ITEM_NOT_EXIST	3


#define TIME_EFFECT_DEATH		400	// thời gian bằng đúng số lượng frame animation* 100 mili seconds
#define TIME_EFFECT_HIT		200

class CTorch:public CGameObject
{
	DWORD dt_die; // đo thời gian cho animation lửa xuất hiện sau khi đánh 
	DWORD dt_strock;
	CItem* item;

	CEffect* effectDie;
	CEffect* effectHit;
	
public:
	bool isStrock;

	CTorch(int type,int ani_id,float _x, float _y); // type item, ani_id item vì ani_id Torch đã parse bằng txt
	~CTorch()
	{
		CGameObject::~CGameObject();
		if (item != NULL)
			delete item;
		if (effectDie != NULL)
			delete effectDie;
		if (effectHit != NULL)
			delete effectHit;
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
