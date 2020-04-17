
#pragma once

#include"GameObject.h"
#include"Simon.h"
#include"Textures.h"

//============DEFINE===============
#define TORCH_WIDTH 32
#define TORCH_HEIGHT 64

#define TORCH_STATE_NOT_EXSIST 0
#define TORCH_STATE_EXSIST 1
#define TORCH_STATE_ITEM 2
#define TORCH_STATE_ITEM_NOT_EXSIST 3


#define ID_WHIPUPGRADE  1
#define ID_DAGGER		2
#define ID_HEART		3

class CTorch:public CGameObject
{
	DWORD dt_die;
	// item
	//int level;
public:

	CTorch(int id = 0, int level = 0);

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	void SetPosition(float _x, float _y) 
	{ 
		x = _x; 
		y = _y; 
		
		
	}
};

