#pragma once
#ifndef __BRICK_H_
#define __BRICK_H_

#include "GameObject.h"

#define BRICK_WIDTH  32
class CBrick : public CGameObject
{
public:
	CBrick() :CGameObject()
	{
		AddAnimation(500);
	}
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
#endif