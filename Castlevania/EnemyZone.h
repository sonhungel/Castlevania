#pragma once
#include "GameObject.h"

#define TIME_CREATE_ZOMBIE	1500

class CEnemyZone;
typedef CEnemyZone* LPENEMYZONE;

class CEnemyZone :public CGameObject
{
	vector<LPGAMEOBJECT> listEnemy;

	float x_leftCreateZombie;
	float x_rightCreateZombie;

	float width;
	float height;

	int trendForZombie;

	DWORD timeCreateEnemy;

	int numberOfEnemyMax;

public:
	CEnemyZone(float _x, float _y, float _width, float _height,int _numberEnemy)
	{
		this->x = _x;
		this->y = _y;

		this->width = _width;
		this->height = _height;

		this->numberOfEnemyMax = _numberEnemy;
		timeCreateEnemy = 0;
	}
	
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	void Render() ;
	void GetBoundingBox(float& left, float& top, float& right, float& bottom);

	void GetEnemy(vector<LPGAMEOBJECT>&listObject);

	bool IsCollisionWithSimon();
};

