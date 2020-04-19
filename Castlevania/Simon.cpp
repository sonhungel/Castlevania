#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include"Torch.h"
#include"WhipNormal.h"
#include"Brick.h"

CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon()
{
	CWhipNormal *rob = CWhipNormal::GetInstance();
	weapons.push_back(rob);
	
	untouchable = 0;
	attack_start = 0;
	trans_start = 0;
	_heart = 5;

	CSimon::AddAnimation(400);		//0. idle left 
	CSimon::AddAnimation(401);		//1. walk left
	CSimon::AddAnimation(402);		//2. jump left
	CSimon::AddAnimation(403);		//3. sit left
	CSimon::AddAnimation(404);		//4. stand attack
	CSimon::AddAnimation(405);		//5. sit attack
	CSimon::AddAnimation(410);		//6. trans
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	// Calculate dx, dy 
	CGameObject::Update(dt);

	// Simple fall down
	vy += SIMON_GRAVITY * dt;
	if (x < 0)
		x = 0;
	if (x > 1370)
		x = 1370;

	vector<LPGAMEOBJECT> listTorch;
	vector<LPGAMEOBJECT> listBrick;
	vector<LPGAMEOBJECT> listObject;

	// lọc object tương ứng vào từng list
	for (int i = 0; i <coObjects->size() ; i++)
	{
		if (dynamic_cast<CTorch*>(coObjects->at(i)))
		{
			CTorch* torch = dynamic_cast<CTorch*>(coObjects->at(i));
			listTorch.push_back(torch);
		}
		else if (dynamic_cast<CBrick*>(coObjects->at(i)))
		{
			CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
			listBrick.push_back(brick);
		}
	}

	if (state == SIMON_STATE_SIT_ATTACK || state == SIMON_STATE_STAND_ATTACK)
	{
		//weapon 0 là roi, sau này phải xây dựng các define cho từng vũ khí, cũng như item
		weapons[0]->SetPosition(x, y);
		weapons[0]->SetTrend(nx);
		weapons[0]->CollisionWithObject(dt, listTorch);
		attack_start = GetTickCount();
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

	// No collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny,rdx,rdy);

		// block 
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) 
			vx = 0;
		if (ny != 0) 
			vy = 0;
	}
	
	/*
	coEvents.clear(); 

	// turn off collision when die 
	if (state != SIMON_STATE_DIE)
		CalcPotentialCollisions(&listTorch, coEvents);

	// reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	// collision occured, proceed normally
	if (coEvents.size() > 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		// phần này nếu quên tìm hiểu lại trong collision detection
		x += dx;

		// Collision logic with items
		// xử lý phần simon đánh roi torch rơi ra item
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT temp = coEventsResult[i];
			if (dynamic_cast<CTorch*>(temp->obj)) // if e->obj is torch 
			{
				CTorch* torch = dynamic_cast<CTorch*>(temp->obj);
				if (torch->GetState() == TORCH_STATE_EXSIST)
				{
					torch->fire_start = GetTickCount();
				}
			}
		}
		
		
	}
	*/

	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani;
	if (state == SIMON_STATE_IDLE)
	{
		ani = SIMON_ANI_IDLE;
	}
	else if (state == SIMON_STATE_SIT)
	{
		ani = SIMON_ANI_SITTING;
	}
	else if (state == SIMON_STATE_JUMP)
	{
		if (vy < 0)
			ani = SIMON_ANI_JUMPING;
		else
			ani = SIMON_ANI_IDLE;
	}
	else if (state == SIMON_STATE_STAND_ATTACK)
	{
		ani = SIMON_ANI_STANDING_ATTACKING;
		weapons[0]->Render();
	}
	else if(state== SIMON_STATE_SIT_ATTACK)
	{
		ani = SIMON_ANI_SITTING_ATTACKING;
		weapons[0]->Render();
	}
	// thiếu attack knife
	else {
		if (vx == 0)
		{
			ani = SIMON_ANI_IDLE;
		}
		else
		{
			ani = SIMON_ANI_WALKING;
		}
	}
	//if (trans_start > 0) {
	//	ani = SIMON_ANI_TRANS;
	//	if (GetTickCount() - trans_start > 200)
	//	{
	//		trans_start = 0;
	//	}
	//}
	
	animations[ani]->RenderTrend(x, y, nx);

	//RenderBoundingBox();
}


void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case SIMON_STATE_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case SIMON_STATE_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case SIMON_STATE_SIT:
		vx = 0;
		break;
	case SIMON_STATE_JUMP:
		if (vy == 0) {
			vy = -SIMON_JUMP_SPEED_Y;
			//vx = 0;
		}
		break;
	case SIMON_STATE_UP:
		y -= 20;

	case SIMON_STATE_IDLE:
		vx = 0;
		break;
	case SIMON_STATE_STAND_ATTACK:
		if (attack_start != 0)
		{
			if (GetTickCount() - attack_start >= ATTACK_TIME)
				attack_start = 0;
		}
		else
		{
			attack_start = GetTickCount();
			vx = 0;
		}
		break;

	case SIMON_STATE_SIT_ATTACK:
		if (attack_start != 0)
		{
			if (GetTickCount() - attack_start >= ATTACK_TIME)
				attack_start = 0;
		}
		else 
		{
			attack_start = GetTickCount();
			vx = 0;
		}
		break;
		// còn phóng dao
	}
	
}

//void CSimon::CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj)
//{
//	for (int i = 0; i < listObj.size(); i++)
//	{
			// chưa xây dựng các item
//	}
//}


void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;
	bottom = this->y + SIMON_HEIGHT_STAND;
	if (state == SIMON_STATE_SIT ||state==SIMON_STATE_SIT_ATTACK)
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}
}

