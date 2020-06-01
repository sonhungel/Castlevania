#pragma once
#ifndef __BRICK_H_
#define __BRICK_H_

#include "GameObject.h"
#include"Game.h"

#define BRICK_WIDTH  32
class CBrick : public CGameObject
{
private:
	int width;
	int height;
public:
	CBrick(int _width,int _height) :CGameObject()
	{
		this->width = _width;
		this->height = _height;
	}
	void Render();
	virtual void GetBoundingBox(float &left, float &top, float &right, float &bottom);
};
#endif