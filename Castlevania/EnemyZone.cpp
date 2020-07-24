#include "EnemyZone.h"
#include"Simon.h"
#include"Game.h"
#include"Zombie.h"

void CEnemyZone::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	float cam_x, cam_y;
	CGame::GetInstance()->GetCamPos(cam_x, cam_y);
	
	x_leftCreateZombie = cam_x;
	x_rightCreateZombie = cam_x + SCREEN_WIDTH;

	if (IsCollisionWithSimon())
	{
		if (listEnemy.size() < numberOfEnemyMax)
		{
			//if (timeCreateEnemy == 0)
			//{
				if (timeCreateEnemy == 0)
					timeCreateEnemy = GetTickCount();
				else if(GetTickCount()-timeCreateEnemy>TIME_CREATE_ZOMBIE)
				{
					timeCreateEnemy = 0;
					srand((unsigned)time(0));
					int item_type = rand() % 9 + 51;

					int sign = rand() & 1 ? -1 : 1;	// random -1, +1
					if (sign == 1)
					{
						
						//int item_type = rand() % 58 + 51;
						LPGAMEOBJECT obj = new CZombie(x_leftCreateZombie-ENEMY_ZOMBIE_WIDTH, CSimon::GetInstance()->y-20, item_type, sign);
						listEnemy.push_back(obj);
					}
					else
					{
						//srand((unsigned)time(0));
						LPGAMEOBJECT obj = new CZombie(x_rightCreateZombie, CSimon::GetInstance()->y-20, item_type, sign);
						listEnemy.push_back(obj);
					}
				}
			//}
		}
	}
	//DebugOut(L"Vi tri simon : %d, %d\n", (int)this->x, (int)this->y);
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
		if (listEnemy.at(i)->blood > 0 && listEnemy.at(i)->x >= cam_x-ENEMY_ZOMBIE_WIDTH && listEnemy.at(i)->x <= cam_x + SCREEN_WIDTH && listEnemy.at(i)->y<=SCREEN_HEIGHT)
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
