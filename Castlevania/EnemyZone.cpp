#include "EnemyZone.h"
#include"Simon.h"
#include"Game.h"

void CEnemyZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	
	x_leftCreateZombie = cam_x;
	x_rightCreateZombie = cam_x + SCREEN_WIDTH;
}

void CEnemyZone::Render()
{
	RenderBoundingBox();
}

void CEnemyZone::GetBoundingBox(float & left, float & top, float & right, float & bottom)
{
	left = x;
	top = y;
	right = x + width;
	bottom = y + height;
}

void CEnemyZone::GetEnemy(vector<LPGAMEOBJECT>& listObject)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	for (UINT i = 0;i < listEnemy.size();i++)
	{
		if (listEnemy.at(i)->blood > 0 && listEnemy.at(i)->x >= cam_x && listEnemy.at(i)->x <= cam_x + SCREEN_WIDTH)
			listObject.push_back(listEnemy.at(i));
		else
		{
			delete listEnemy.at(i);
			listEnemy.erase(listEnemy.begin() + i);
		}
	}
}

bool CEnemyZone::IsCollisionWithSimon()
{
	RECT rect1, rect2;

	float l1, t1, r1, b1;
	float l2, t2, r2, b2;

	GetBoundingBox(l1, t1, r1, b1);
	rect1.left = (int)l1;
	rect1.top = (int)t1;
	rect1.right = (int)r1;
	rect1.bottom = (int)b1;

	CSimon::GetInstance()->GetBoundingBox(l2, t2, r2, b2);

	rect2.left = (int)l2;
	rect2.top = (int)t2;
	rect2.right = (int)r2;
	rect2.bottom = (int)b2;

	return CGame::GetInstance()->isCollision(rect1, rect2);
}
