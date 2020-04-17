#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"

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

	vector<LPCOLLISIONEVENT> listTorch;

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
		
		// Xử lý collision logic với các object khác
	}

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
	}
}

void CSimon::CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
}


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

