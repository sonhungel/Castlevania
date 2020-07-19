
#include "Whip.h"
#include "Torch.h"
#include "Game.h"
#include"Effect.h"
#include"Define.h"
#include"Brick.h"
#include"Candle.h"
#include"BlackKnight.h"


CWhip* CWhip::__instance = NULL;

CWhip* CWhip::GetInstance()
{
	if (__instance == NULL) __instance = new CWhip();
	return __instance;
}

CWhip::CWhip()
{
	type = eType::WEAPON_WHIP;
	_level = 1;
	AddAnimation(WHIP_LEVEL_1_ID);
	AddAnimation(WHIP_LEVEL_2_ID); // level 2
	AddAnimation(WHIP_LEVEL_3_ID);	// level 3
	animation = animations[ANI_WHIP_LEVEL_1]; // whip level 1
}

void CWhip::SetPosition(float x, float y)
{
	if (_level == 1||_level==2)
	{
		if (nx < 0)
		{
			this->x = x - 47;
		}
		else {
			this->x = x - 7;
		}
	}
	else if (_level == 3)
	{
		if (nx < 0)
		{
			this->x = x - 80;
		}
		else {
			this->x = x -7;
		}
	}
	this->y = y + 8;
}

void CWhip::Render()
{
	animation = animations[_level - 1];
	animation->RenderTrend(x, y, nx);
	RenderBoundingBox();
}

void CWhip::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listObject;
	// collision logic with item
	for (UINT i=0; i < listObject.size(); i++)
	{
		LPGAMEOBJECT object = coObjects->at(i);
		listObject.push_back(object);
	}
	//animations[_level - 1]->ResetFrame();
	CollisionWithObject(dt, listObject);
}

void CWhip::setUpLevel()
{
	if (_level < 3) _level++;
	animation = animations[_level - 1];
}

void CWhip::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (animation->GetCurrentFrame() < 2)
		return;
	if (_level == 1 || _level == 2)
	{
		if (nx > 0)
		{
			left = x + 40;
			right = x + WHIPNORMAL_WIDTH;
			top = y + 5;
			bottom = y + WHIPNORMAL_HEIGHT;
		}
		else
		{
			left = x ;
			right = x + WHIPNORMAL_WIDTH-40;
			top = y + 5;
			bottom = y + WHIPNORMAL_HEIGHT;
		}
	}
	else
	{
		if (nx > 0)
		{
			left = x+40;
			right = x + WHIPLONG_WIDTH;
			top = y+5;
			bottom = y + WHIPNORMAL_HEIGHT;
		}
		else
		{
			left = x;
			right = x + WHIPLONG_WIDTH-40;
			top = y+5;
			bottom = y + WHIPNORMAL_HEIGHT;
		}
	}
}

void CWhip::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (animation->GetCurrentFrame() < 2)
		return;

	RECT rect1, rect2;

	float l1, t1, r1, b1;
	float l2, t2, r2, b2;
	// Get bounding box of whip
	GetBoundingBox(l1, t1, r1, b1);
	rect1.left = (int)l1;
	rect1.top = (int)t1;
	rect1.right = (int)r1;
	rect1.bottom = (int)b1;

	for (int i=0;i<listObj.size();i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			CTorch* torch = dynamic_cast<CTorch*>(listObj.at(i));
			if (listObj.at(i)->GetState() == STATE_TORCH_EXIST)
			{
				// get bounding box of the object that whip collision
				listObj.at(i)->GetBoundingBox(l2, t2, r2, b2); 
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					torch->isStrock = true;
					torch->SetState(STATE_TORCH_NOT_EXIST);
				}
			}
		}
		if (dynamic_cast<CCandle*>(listObj.at(i)))
		{
			CCandle* candle = dynamic_cast<CCandle*>(listObj.at(i));
			if (candle->GetState() == STATE_CANDLE_EXIST)
			{
				candle->GetBoundingBox(l2,t2,r2,b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					candle->isStrock = true;
					candle->SetState(STATE_CANDLE_NOT_EXIST);
				}
			}
		}
		if (dynamic_cast<CEnemy*>(listObj.at(i)))
		{
			
			if (listObj.at(i)->GetState() == STATE_ENEMY_EXIST)
			{
				CEnemy* enemy = dynamic_cast<CEnemy*>(listObj.at(i));
				enemy->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					if(enemy->blood>1)
						enemy->isStrock = true;
					// bên trong enemey sẽ tự bộng từ blood qua cờ isStrock 
				}
				
			}
		}
		
	}
}

