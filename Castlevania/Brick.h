﻿#pragma once
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
	}
	virtual void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
#endif