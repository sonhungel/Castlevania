
#include "WhipNormal.h"
#include "Torch.h"
#include "Game.h"

CWhipNormal* CWhipNormal::__instance = NULL;

CWhipNormal* CWhipNormal::GetInstance()
{
	if (__instance == NULL) __instance = new CWhipNormal();
	return __instance;
}

CWhipNormal::CWhipNormal()
{
	_level = 1;
	AddAnimation(600);
	AddAnimation(601);
	AddAnimation(602);
	animation = animations[0];
}

void CWhipNormal::SetPosition(float simon_x, float simon_y)
{
	if (_level == 1 || _level == 2)
	{
		if (nx < 0)
		{
			x = simon_x - 50;
		}
		else {
			x = simon_x - 10;
		}
	}
	else
	{
		if (nx < 0)
		{
			x = simon_x - 80;
		}
		else {
			x = simon_x - 10;
		}
	}
	y = simon_y;
}

void CWhipNormal::Render()
{
	animation->RenderTrend(x, y, nx);
	RenderBoundingBox();
}

void CWhipNormal::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPGAMEOBJECT> listObject;
	// collision logic with item
	for (UINT i=0; i < listObject.size(); i++)
	{
		LPGAMEOBJECT object = coObjects->at(i);
		listObject.push_back(object);
	}
	animations[_level - 1]->ResetFrame();
	CollisionWithObject(dt, listObject);
}

void CWhipNormal::setUpLevel()
{
	if (_level < 3) _level++;
	animation = animations[_level - 1];
}

void CWhipNormal::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (_level == 1 || _level == 2)
	{
		left = x;
		right = x + 120;
		top = y;
		bottom = y + 30;
	}
	else
	{
		left = x;
		right = x + 145;
		top = y;
		bottom = y + 30;

	}
}

void CWhipNormal::CollisionWithObject(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	if (animation->GetCurrentFrame() < 2)
		return;

	RECT rect1, rect2;

	float l1, t1, r1, b1;
	float l2, t2, r2, b2;

	GetBoundingBox(l1, t1, r1, b1);
	rect1.left = (int)l1;
	rect1.top = (int)t1;
	rect1.right = (int)r1;
	rect1.bottom = (int)b1;

	for (int i=0;i<listObj.size();i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == TORCH_STATE_EXSIST)
			{
				listObj.at(i)->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					listObj.at(i)->SetState(TORCH_STATE_NOT_EXSIST);

				}
			}
		}
	}

}

