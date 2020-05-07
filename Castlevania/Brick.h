#pragma once
#ifndef __BRICK_H_
#define __BRICK_H_

#include "GameObject.h"
#include"Game.h"

#define BRICK_WIDTH  32
class CBrick : public CGameObject
{
public:
	CBrick() :CGameObject()
	{
		if(CGame::GetInstance()->GetIDCurrentScene()==1)
			AddAnimation(496);
		if(CGame::GetInstance()->GetIDCurrentScene()==2|| CGame::GetInstance()->GetIDCurrentScene() == 3)
			AddAnimation(497);
		if (CGame::GetInstance()->GetIDCurrentScene() == 4 || CGame::GetInstance()->GetIDCurrentScene() == 5)
			AddAnimation(498);
		if (CGame::GetInstance()->GetIDCurrentScene() == 6)
			AddAnimation(499);
	}
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
#endif