
#pragma once

#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"

//===========DEFINE================

#define STATE_ITEM_NOT_EXSIST	0
#define STATE_ITEM_EXSIST		1

#define TYPE_ITEM				0
#define TYPE_ITEM_KNIFE			1
#define TYPE_ITEM_WHIPUPGRADE	2
#define TYPE_ITEM_HEART			3

#define GRAVITY_ITEM		  0.03f

class CItem:public CGameObject
{
protected:
	int type_Item; // định dang item
public:
	CItem() :CGameObject()
	{
		state = STATE_ITEM_EXSIST;
		type_Item = TYPE_ITEM;
	}
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual int getType() { return type_Item; }
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

