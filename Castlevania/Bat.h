#pragma once
#include "GameObject.h"
#include"Enemy.h"

#define ENEMY_BAT_ANI_ID_IDLE	1002
#define ENEMY_BAT_ANI_ID_FLY	1003

#define BAT_BBOX_WIDTH 32
#define BAT_BBOX_HEIGHT 32

#define DISTANCE_FROM_PREPOSITION_TO_BOTTOM_LIMIT	128	// đã đo trong game thực tế với khoảng cách 4 viên gạch


class CBat :public CEnemy
{
private:
	float topLimit;
	float bottomLimit;
};

