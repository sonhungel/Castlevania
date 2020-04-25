#include <algorithm>
#include "debug.h"

#include "Simon.h"
#include "Game.h"
#include"Torch.h"
#include"Whip.h"
#include"Brick.h"
#include"Knife.h"

CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon()
{
	CWhip *whip = CWhip::GetInstance();
	weapons.push_back(whip);
	
	untouchable = 0;
	attack_start = 0;
	trans_start = 0;
	_heartCount = 5;

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
	vector<LPGAMEOBJECT> listItem;

	// lọc object tương ứng vào từng list để thuận tiện cho việc xử lý va chạm cũng như update
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
		if (dynamic_cast<CItem*>(coObjects->at(i)))
		{
			CItem* item = dynamic_cast<CItem*>(coObjects->at(i));
			listItem.push_back(item);
		}
	}

	if (state == STATE_SIMON_SIT_ATTACK || state == STATE_SIMON_STAND_ATTACK)
	{
		//weapon 0 is whip
		weapons[0]->SetPosition(x, y);
		weapons[0]->SetTrend(nx);
		weapons[0]->CollisionWithObject(dt, listTorch);
		attack_start = GetTickCount();
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	// turn off collision when die 
	if (state != STATE_SIMON_DIE)
		CalcPotentialCollisions(&listBrick, coEvents);

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
	
	coEvents.clear(); 

	// turn off collision when die 
	if (state != STATE_SIMON_DIE)
		CalcPotentialCollisions(&listTorch, coEvents); // 

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
		x += dx;

		// Collision logic with item
		
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT temp = coEventsResult[i];
			if (dynamic_cast<CTorch*>(temp->obj)) // if e->obj is torch 
			{
				CTorch* torch = dynamic_cast<CTorch*>(temp->obj);
				if (torch->GetState() == STATE_TORCH_EXSIST)
				{
					
				}
				else
				{
					if (dynamic_cast<CItem*>(torch->GetItem()))	// check item					
					{
						CItem* item = dynamic_cast<CItem*>(torch->GetItem());
						listItem.push_back(item);
						torch->SetState(STATE_TORCH_ITEM_NOT_EXSIST); // item  eated
					}
				}
			}
		}
		CollisionWithItem(dt, listItem);
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::Render()
{
	int ani = 0;
	if (state == STATE_SIMON_DIE)
	{
		ani = ANI_SIMON_IDLE;
	}
	else if (state == STATE_SIMON_SIT)
	{
		ani = ANI_SIMON_SITTING;
	}
	else if (state == STATE_SIMON_JUMP)
	{
		if (vy < 0)
			ani = ANI_SIMON_JUMPING;
		else
			ani = ANI_SIMON_IDLE;
	}
	else if (state == STATE_SIMON_STAND_ATTACK)
	{
		ani = ANI_SIMON_STANDING_ATTACKING;
		weapons[0]->Render();
	}
	else if(state== STATE_SIMON_SIT_ATTACK)
	{
		ani = ANI_SIMON_SITTING_ATTACKING;
		weapons[0]->Render();
	}
	else if (state == STATE_SIMON_ATTACK_KNIFE)
	{
		if(weapons.size()>1)
			ani = ANI_SIMON_STANDING_ATTACKING;
	}
	else {
		if (vx == 0)
		{
			if(state!=STATE_SIMON_SIT_ATTACK||state!=STATE_SIMON_STAND_ATTACK)
			ani = ANI_SIMON_IDLE;
		}
		else
		{
			ani = ANI_SIMON_WALKING;
		}
	}
	
	
	animations[ani]->RenderTrend(x, y, nx);

	RenderBoundingBox();
}


void CSimon::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case STATE_SIMON_WALKING_RIGHT:
		vx = SIMON_WALKING_SPEED;
		nx = 1;
		break;
	case STATE_SIMON_WALKING_LEFT:
		vx = -SIMON_WALKING_SPEED;
		nx = -1;
		break;
	case STATE_SIMON_SIT:
		//vx = 0;
		break;
	case STATE_SIMON_JUMP:
		if (vy == 0) {
			vy = -SIMON_JUMP_SPEED_Y;
			//vx = 0;
		}
		break;
	case STATE_SIMON_UP:
		y -= 20;
	case STATE_SIMON_IDLE:
		vx = 0;
		break;
	case STATE_SIMON_STAND_ATTACK:
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

	case STATE_SIMON_SIT_ATTACK:
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
	case STATE_SIMON_ATTACK_KNIFE:
		vx = 0;
		if (weapons.size() > 1)
		{
			CKnife* knife = CKnife::GetInstance();
			if (knife->GetState() == STATE_KNIFE_HIDE)
			{
				knife->SetState(STATE_KNIFE_APPEAR);
				knife->SetPosition(x, y);
				knife->SetTrend(nx);
			}
		}
		break;

	}
	
}
void CSimon::CollisionWithItem(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (listObj.at(i)->GetState() == STATE_ITEM_EXSIST)
		{
			if (listObj.at(i)->getType() == TYPE_ITEM_HEART) // item heart
			{
				_heartCount += 5;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			if (listObj.at(i)->getType() == TYPE_ITEM_WHIPUPGRADE)	// item whipUpgrade
			{
				CWhip::GetInstance()->setUpLevel();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			if (listObj.at(i)->getType() == TYPE_ITEM_KNIFE)	// item knife
			{
				CKnife* knife = CKnife::GetInstance();
				weapons.push_back(knife);
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
		}
	}
}


void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;
	bottom = this->y + SIMON_HEIGHT_STAND;
	if (state == STATE_SIMON_SIT ||state== STATE_SIMON_SIT_ATTACK)
	{
		bottom = this->y + SIMON_HEIGHT_SIT;
	}
}

