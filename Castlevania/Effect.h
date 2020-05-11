#pragma once
#include"GameObject.h"

#define EFFECT_WIDTH 25
#define EFFECT_HEIGHT 37

class CEffect:public CGameObject
{
	bool isDone;
public:
	CEffect(int x,int y,int animationID)
	{
		this->x = x;
		this->y = y;
		isDone = false;
		AddAnimation(animationID);
	}
	void Update();
	void Render();
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);
	bool CheckIsDone() { return isDone; }// for effect
	CAnimation* GetAnimation() { if (animations.size() > 0)return animations[0]; } // get animation off effect để tính frame thay vì đo thời gian
};
