
#pragma once

#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"


//============DEFINE============

#define ITEM_STATE_NOT_EXSIST 0
#define ITEM_STATE_EXSIST 1

#define TYPE_ITEM			  0
#define TYPE_ITEM_DAGGER	  1
#define TYPE_ITEM_WHIPUPGRADE 2
#define TYPE_ITEM_HEART		  3

#define ITEM_GRAVITY		  0.05f

class CItem:public CGameObject
{
protected:
	int _type;
public:
	CItem()
	{
		state = ITEM_STATE_EXSIST;
		_type = TYPE_ITEM;
	}
	virtual int getType() { return _type; }
	void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

