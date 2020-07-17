﻿#include <algorithm>
#include"Utils.h"

#include "Simon.h"
#include "Game.h"
#include"Torch.h"
#include"Whip.h"
#include"Brick.h"
#include"Knife.h"
#include"Axe.h"
#include"Portal.h"
#include"ItemMoney.h"
#include"Boomerang.h"
#include"HollyWater.h"
#include"Platform.h"
#include"Candle.h"
#include"BreakBrick.h"
#include"Bat.h"
#include"BlackKnight.h"
#include"Enemy.h"


CSimon* CSimon::__instance = NULL;

CSimon* CSimon::GetInstance()
{
	if (__instance == NULL) __instance = new CSimon();
	return __instance;
}

CSimon::CSimon()
{
	whip = CWhip::GetInstance();

	listSubWeapon.push_back(CKnife::GetInstance());		// knife 0
	listSubWeapon.push_back(CAxe::GetInstance());		// axe 1
	listSubWeapon.push_back(CBoomerang::GetInstance());	// boomerang 2
	listSubWeapon.push_back(CHollyWater::GetInstance());// hollywater 3
	
	untouchable = false;

	untouchable_start = 0;
	trans_start = 0;

	subWeapon = eType::WEAPON_AXE;

	isBeingOnStair = false;
	isCanOnStair = 0;
	isAutoGo = false;
	_stairTrend = -1;
	auto_x = -1;

	idScene_current = 1;
	idScene_next = 2;

	this->blood = MAX_BLOOD;
	_heart = 0;
	_score = 0;
	_live = 5;

	isCanAttack = true;
}

void CSimon::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects)
{
	
	if (isAutoGo)
	{
		CalculateAutoGo();
		if (abs(auto_x - x) > 0.5f)
		{
			x += nx;
		}
		else
		{
			isAutoGo = false;
			
			if (isCanOnStair == 1)
			{
				state = STATE_SIMON_GO_UP;
				y = y - SIMON_PER_STEP;
				if (_stairTrend == -1)
				{
					x = x + SIMON_PER_STEP;
					nx = 1;
				}
				else
				{
					nx = -1;
					x = x - SIMON_PER_STEP;
				}
			}
			else if(isCanOnStair==-1)
			{
				state = STATE_SIMON_GO_DOWN;
				y = y + SIMON_PER_STEP;
				if (_stairTrend == -1)
				{
					nx = -1;
					x = x - SIMON_PER_STEP;
				}
				else
				{
					nx = 1;
					x = x + SIMON_PER_STEP;
				}
			}
		}
		return;
	}

	if (attack_start > 0)
	{
		if (GetTickCount() - attack_start > ATTACK_TIME)
		{
			attack_start = 0;
		}
	}
	if (attack_start_temp > 0)
	{
		if (GetTickCount() - attack_start_temp > ATTACK_TIME_WAIT)
		{
			isCanAttack = true;
			attack_start_temp = 0;
		}
	}
	if (trans_start > 0)
	{
		vx = 0;
		if (GetTickCount() - trans_start > TRANSITION_TIME)
		{
			trans_start = 0;
		}
	}
	else 
	{ 
		vector<LPGAMEOBJECT> listCoObjects;
		vector<LPGAMEOBJECT> listHideObject;
		vector<LPGAMEOBJECT> listCoObjectForWhip;
		vector<LPGAMEOBJECT> listCoObjectforSubWeapon;
		vector<LPGAMEOBJECT> listEnemy;

		// Lọc
		for (UINT i = 0; i < coObjects->size(); i++)
		{
			if (dynamic_cast<CHidenObject*>(coObjects->at(i)))
			{
				CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(coObjects->at(i));
				listHideObject.push_back(hidenObj);
			}
			else if(dynamic_cast<CBrick*>(coObjects->at(i))
				|| dynamic_cast<CPlatform*>(coObjects->at(i))
				|| dynamic_cast<CBreakBrick*>(coObjects->at(i))
				|| dynamic_cast<CPortal*>(coObjects->at(i)))
			{
				listCoObjects.push_back(coObjects->at(i));
				if (dynamic_cast<CBreakBrick*>(coObjects->at(i)))
					listCoObjectForWhip.push_back(coObjects->at(i));
				if (dynamic_cast<CBrick*>(coObjects->at(i)))
					listCoObjectforSubWeapon.push_back(coObjects->at(i));
			}
			else
			{
				if(dynamic_cast<CEnemy*>(coObjects->at(i)))
					listEnemy.push_back(coObjects->at(i));
				listCoObjectForWhip.push_back(coObjects->at(i));
				listCoObjectforSubWeapon.push_back(coObjects->at(i));
			}
		}


		// xử lý phần stair
		if (isBeingOnStair)
		{
			if (state == STATE_SIMON_GO_DOWN)
			{
				if (_stairTrend == -1)	// stair left
				{
					nx = -1;
					vx = -SIMON_SPEED_ON_STAIR;
					vy = SIMON_SPEED_ON_STAIR;
				}
				else  // stair right
				{
					nx = 1;
					vx = SIMON_SPEED_ON_STAIR;
					vy = SIMON_SPEED_ON_STAIR;
				}
			}
			else if (state == STATE_SIMON_GO_UP)
			{
				if (_stairTrend == -1)	// stair left
				{
					nx = 1;
					vx = SIMON_SPEED_ON_STAIR;
					vy = -SIMON_SPEED_ON_STAIR;
				}
				else  // stair right
				{
					nx = -1;
					vx = -SIMON_SPEED_ON_STAIR;
					vy = -SIMON_SPEED_ON_STAIR;
				}
			}
			else
			{
				vx = 0;
				vy = 0;
			}
		}
		else
		{
			vy += SIMON_GRAVITY * dt;
		}
		
		CGameObject::Update(dt);
		
		if (isBeingOnStair == true)	// tránh trường hợp va chạm gạch khi đang trên thang
		{
			x += dx;
			y += dy;
		}

		if (listHideObject.size() > 0)
			IsCanOnStair(listHideObject); // dùng để bắt đầu thang, còn việc phát hiện va chạm swept AABB là để kết thúc thang
		//listHideObject.clear();

		if (state == STATE_SIMON_SIT_ATTACK || 
			state == STATE_SIMON_STAND_ATTACK||
			state == STATE_SIMON_GO_DOWN_ATTACK||
			state == STATE_SIMON_GO_UP_ATTACK)
		{
			//whip->SetPosition(x, y);
			whip->SetTrend(nx);
			whip->CollisionWithObject(dt, listCoObjectForWhip);
		}
		CollisionWithObjectHaveItem(dt, listCoObjectForWhip);
		listCoObjectForWhip.clear();
		for (UINT i = 0;i < listSubWeapon.size();i++)
		{
			listSubWeapon.at(i)->Update(dt, &listCoObjectforSubWeapon);
		}
		listCoObjectforSubWeapon.clear();

		CollisionWithEnemy(dt, listEnemy);
		

		// reset untouchable timer if untouchable time has passed
		if (GetTickCount() - untouchable_start > SIMON_UNTOUCHABLE_TIME)
		{
			untouchable_start = 0;
			untouchable = false;
		}
		else if (GetTickCount() - untouchable_start < SIMON_HURT_TIME && untouchable == true)
		{
			state = STATE_SIMON_HURT;
		}
		else
		{
			//state = STATE_SIMON_IDLE;
		}

		if (blood <= 0)
			state = STATE_SIMON_DIE;
		
		// SubWeapon
#pragma region subweapon
		if (state == STATE_SIMON_ATTACK_SUBWEAPON)
		{
			if (subWeapon != -1)
			{
				LoadSubWeapon(subWeapon);
			}
		}
#pragma endregion
	
		// Collsion
#pragma region collsion

		// Xử Lý va chạm kết thúc thang khi đang ở trên thang
		if (isBeingOnStair)
		{
			CollisionWithHidenObject(dt, listHideObject);
		}
		listHideObject.clear();

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();
		coEventsResult.clear();


		// turn off collision when die 
		CalcPotentialCollisions(&listCoObjects, coEvents);

		// No collision occured, proceed normally
		if (coEvents.size() == 0 && isBeingOnStair == false)
		{
			x += dx;
			y += dy;
		}
		else// Xử lý collision for simon
		{

			float min_tx, min_ty, nx = 0, ny=0;
			float rdx = 0;
			float rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			//
			// Collision logic with objects
			//
	
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CPortal*>(e->obj))
				{
					CPortal* portal = dynamic_cast<CPortal*>(e->obj);
					DebugOut(L"[INFO] Collision with portal\n");
					CGame::GetInstance()->tagSwitchScene = portal->GetSceneId();
					idScene_current = CGame::GetInstance()->GetIDCurrentScene();
					idScene_next = portal->GetSceneId();
					if (idScene_next < idScene_current)
					{
						CGame::GetInstance()->tagGoBackScene = true;
					}
				}

				else if (dynamic_cast<CBrick*>(e->obj))
				{
					if (isBeingOnStair == false)
					{
						CollisionWithBrick(dt, e->obj, min_tx, min_ty, nx, ny, rdx, rdy);
					}

				}
				else if (dynamic_cast<CBreakBrick*>(e->obj))		// Chưa Xử lý
				{
					x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
					y += min_ty * dy + ny * 0.4f;

					if (nx != 0)
						vx = 0;
					if (ny != 0)
						vy = 0;
				}
				else if (dynamic_cast<CPlatform*>(e->obj))
				{
					CollisionWithPlatform(dt, e->obj, min_tx, min_ty, nx, ny, rdx, rdy);
				}
			}
		}
		// clean up collision events
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
		listCoObjects.clear();
	}

	
	//DebugOut(L"Vi tri simon : %d, %d\n",(int)this->x,(int)this->y); 

	//float l1, t1, r1, b1;
	// Get bounding box of whip
	//GetBoundingBox(l1, t1, r1, b1);

	//DebugOut(L"high simon : %d\n", (int)b1-(int)t1);
#pragma endregion
	//DebugOut(L"State simon : %d\n", (int)this->state);
}

void CSimon::Render()
{
	for (UINT i = 0;i < listSubWeapon.size();i++)
	{
		if(listSubWeapon.at(i)->GetState()==STATE_SUBWEAPON_APPEAR)
			listSubWeapon.at(i)->Render();
	}

	int ani = 0;

	if (state == STATE_SIMON_DIE)
	{
		ani = ANI_SIMON_DIE;
	}
	else if (state == STATE_SIMON_IDLE)
	{
		if (isBeingOnStair == false && isSimonOnAir == false)
			ani = ANI_SIMON_IDLE;
	}
	else if (state == STATE_SIMON_SIT)
	{
		ani = ANI_SIMON_SITTING;
	}
	else if (state == STATE_SIMON_JUMP)
	{
		if (isBeingOnStair == false)
		{
			if (isSimonOnAir==true)
				ani = ANI_SIMON_JUMPING;
			else
				ani = ANI_SIMON_IDLE;
		}
	}
	else if (state == STATE_SIMON_STAND_ATTACK)
	{
		ani = ANI_SIMON_STANDING_ATTACKING;
		whip->SetPosition(x, y);
		whip->GetAnimation()->SetFrame(animations[ANI_SIMON_STANDING_ATTACKING]->GetCurrentFrame());
		whip->Render();
	}
	else if (state == STATE_SIMON_SIT_ATTACK)
	{
		whip->GetAnimation()->SetFrame(animations[ANI_SIMON_SITTING_ATTACKING]->GetCurrentFrame());
		whip->SetPosition(x, y);
		ani = ANI_SIMON_SITTING_ATTACKING;
		whip->Render();
	}
	else if (state == STATE_SIMON_GO_DOWN_ATTACK)
	{
		if (isBeingOnStair)
		{
			ani = ANI_SIMON_GO_DOWN_ATTACK;
			whip->SetPosition(x, y);
			whip->GetAnimation()->SetFrame(animations[ANI_SIMON_GO_DOWN_ATTACK]->GetCurrentFrame());
			whip->Render();
		}
	}
	else if (state == STATE_SIMON_GO_UP_ATTACK)
	{
		if (isBeingOnStair)
		{
			ani = ANI_SIMON_GO_UP_ATTACK;
			whip->SetPosition(x, y);
			whip->GetAnimation()->SetFrame(animations[ANI_SIMON_GO_UP_ATTACK]->GetCurrentFrame());
			whip->Render();
		}
	}
	else if (state == STATE_SIMON_ATTACK_SUBWEAPON)
	{
		if (subWeapon!=-1)
			ani = ANI_SIMON_STANDING_ATTACKING;
	}
	else if (trans_start > 0) {
		ani = ANI_SIMON_TRANS;
	}
	else if (isAutoGo)
	{
		ani = ANI_SIMON_WALKING;
	}
	else if (state == STATE_SIMON_IDLE_DOWN)
	{
		ani = ANI_SIMON_IDLE_DOWN;
	}
	else if (state == STATE_SIMON_IDLE_UP)
	{
		ani = ANI_SIMON_IDLE_UP;
	}
	else if (state == STATE_SIMON_GO_DOWN)
	{
		if (isBeingOnStair|| isCanOnStair == -1 )
			ani = ANI_SIMON_GO_DOWN;
		else
			ani = ANI_SIMON_SITTING;
	}
	else if (state == STATE_SIMON_GO_UP && isBeingOnStair)
	{
		ani = ANI_SIMON_GO_UP;
	}
	else if (state == STATE_SIMON_HURT)
	{
		ani = ANI_SIMON_HURT;
	}
	else 
	{
		if (vx == 0)
		{
			if(state!=STATE_SIMON_SIT_ATTACK||state!=STATE_SIMON_STAND_ATTACK&&state!=STATE_SIMON_ATTACK_SUBWEAPON&&isBeingOnStair==false)
				ani = ANI_SIMON_IDLE;
		}
		else
		{
			if(isSimonOnAir==false)
				ani = ANI_SIMON_WALKING;
		}
	}
	if (isSimonOnAir&&state != STATE_SIMON_HURT &&
		state != STATE_SIMON_ATTACK_SUBWEAPON &&
		state != STATE_SIMON_GO_DOWN_ATTACK &&
		state != STATE_SIMON_GO_UP_ATTACK &&
		state != STATE_SIMON_STAND_ATTACK &&
		state != STATE_SIMON_SIT_ATTACK)
		ani = ANI_SIMON_JUMPING;

	int alpha = 255;
	//if (untouchable) alpha = 128;
	if (untouchable==true && (GetTickCount() - untouchable_start > SIMON_HURT_TIME)) alpha = 150;
	animations[ani]->RenderTrend(x, y, nx,alpha);

	RenderBoundingBox();

	//DebugOut(L" ANI_ID simon : %d\n", ani);
	
	//DebugOut(L" STATE simon : %d\n", this->state);
}


void CSimon::SetState(int state)
{

	//if (animations[ANI_SIMON_STANDING_ATTACKING]->GetCurrentFrame() > 0)
	//{
	//}
	//else if (animations[ANI_SIMON_SITTING_ATTACKING]->GetCurrentFrame() > 0)
	//{
	//}
	//else if (animations[ANI_SIMON_GO_DOWN_ATTACK]->GetCurrentFrame() > 0)
	//{
	//}
	//else if (animations[ANI_SIMON_GO_UP_ATTACK]->GetCurrentFrame() > 0)
	//{
	//}
	if (trans_start > 0)
	{
	}
	else if (isAutoGo)
	{
	}
	else if (animations[ANI_SIMON_GO_UP]->GetCurrentFrame() > 1 && isBeingOnStair)
	{
	}
	else if (animations[ANI_SIMON_GO_DOWN]->GetCurrentFrame() > 1 && isBeingOnStair)
	{
	}
	else if (attack_start > 0)
	{
	}
	else if (untouchable == true && (GetTickCount() - untouchable_start < SIMON_HURT_TIME))
	{
		vy = 0;
	}
	else
	{
		CGameObject::SetState(state);
		switch (state)
		{
		case STATE_SIMON_WALKING_RIGHT:
			vx = SIMON_WALKING_SPEED;
			nx = SIMON_TREND_RIGHT;
			break;
		case STATE_SIMON_WALKING_LEFT:
			vx = -SIMON_WALKING_SPEED;
			nx = SIMON_TREND_LEFT;
			break;
		case STATE_SIMON_SIT:
			vx = 0;
			break;
		case STATE_SIMON_JUMP:
			if (vy == 0 && isBeingOnStair == false) {
				vy = -SIMON_JUMP_SPEED_Y;
				isSimonOnAir = true;
				//vx = 0;
			}
			break;
		case STATE_SIMON_UP:
			y -= 10;
		case STATE_SIMON_IDLE:
			vx = 0;
			break;
		case STATE_SIMON_STAND_ATTACK:
			attack_start = GetTickCount();
			attack_start_temp = GetTickCount();
			isCanAttack = false;
			vx = 0;
			break;
		case STATE_SIMON_SIT_ATTACK:
			attack_start = GetTickCount();
			attack_start_temp = GetTickCount();
			isCanAttack = false;
			vx = 0;
			break;
		case STATE_SIMON_GO_UP_ATTACK:
			attack_start = GetTickCount();
			attack_start_temp = GetTickCount();
			isCanAttack = false;
			vx = 0;
			vy = 0;
			break;
		case STATE_SIMON_GO_DOWN_ATTACK:
			attack_start = GetTickCount();
			attack_start_temp = GetTickCount();
			isCanAttack = false;
			vx = 0;
			vy = 0;
			break;
		case STATE_SIMON_ATTACK_SUBWEAPON:
			attack_start = GetTickCount();
			attack_start_temp = GetTickCount();
			isCanAttack = false;
			vx = 0;
			break;
		case STATE_SIMON_GO_UP:

			if (isBeingOnStair)
			{
				break;
			}
			if (isCanOnStair != 1)
			{
				vx = 0;
				this->state = STATE_SIMON_IDLE;
			}
			else
			{
				isBeingOnStair = true;
				if (abs(auto_x - x) > 0.5f)
					isAutoGo = true;
			}
			break;
		case STATE_SIMON_GO_DOWN:
			if (isBeingOnStair)
			{
				break;
			}
			if (isCanOnStair != -1)
			{
				vx = 0;
				this->state = STATE_SIMON_SIT;
			}
			else
			{
				isBeingOnStair = true;
				if (abs(auto_x - x) > 0.5f)
					isAutoGo = true;
			}
			break;
		case STATE_SIMON_IDLE_UP:
			vx = vy = 0;
			break;
		case STATE_SIMON_IDLE_DOWN:
			vx = vy = 0;
			break;
		case STATE_SIMON_HURT:
			vx = vy = 0;
			break;
		}
	}
	
}
void CSimon::CollisionWithItem( vector<LPGAMEOBJECT>& listObj)
{
	for (int i = 0; i < listObj.size(); i++)
	{
		if (listObj.at(i)->GetState() == STATE_ITEM_EXSIST)
		{
			if (listObj.at(i)->getType() == eType::ITEM_HEARTBIG) // item heart Big
			{
				if(trans_start==0)
					trans_start = GetTickCount();
				_heart += 10;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_WHIPUPGRADE)	// item whipUpgrade
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				whip->setUpLevel();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_KNIFE)	// item knife
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				subWeapon = eType::WEAPON_KNIFE;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_AXE)
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				subWeapon = eType::WEAPON_AXE;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_BOONGMERANG)
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				subWeapon = eType::WEAPON_BOOMERANG;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_HOLLYWATTER)
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				subWeapon = eType::WEAPON_HOLLYWATER;
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_SMALLHEART)
			{
				_heart += 5;
				if (trans_start == 0)
					trans_start = GetTickCount();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_RED_MONEY||
				listObj.at(i)->getType() == eType::ITEM_YELLOW_MONEY||
				listObj.at(i)->getType() == eType::ITEM_PURPLE_MONEY||
				listObj.at(i)->getType()==eType::ITEM_BLUE_MONEY)
			{
				CItemMoney* item = dynamic_cast<CItemMoney*>(listObj.at(i));
				item->isEated = true;
				//if (trans_start == 0)
					//trans_start = GetTickCount();
			}
			else if (listObj.at(i)->getType() == eType::ITEM_CLOCK)	// hoàn thiện sau
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_CROSS)	// hoàn thiện sau
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
			else if (listObj.at(i)->getType() == eType::ITEM_VASE)	// hoàn thiện sau
			{
				if (trans_start == 0)
					trans_start = GetTickCount();
				listObj.at(i)->SetState(STATE_ITEM_NOT_EXSIST);
			}
		}
	}
}

void CSimon::CollisionWithBrick(DWORD dt, LPGAMEOBJECT brick, float min_tx0, float min_ty0, int nx0, int ny0, 
																										float rdx0, float rdy0)
{
	vector<LPGAMEOBJECT> listObject;
	listObject.push_back(brick);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(&listObject, coEvents);

	float min_tx, min_ty, nx = 0, ny;
	float rdx = 0;
	float rdy = 0;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

	if (min_tx <= min_tx0)
		x += min_tx * dx + nx * 0.4f;		// nx*0.4f : need to push out a bit to avoid overlapping next frame
	if (min_ty <= min_ty0)
		y += min_ty * dy + ny * 0.4f;

	if (nx != 0)
		vx = 0;

	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];
		if (dynamic_cast<CBrick*>(e->obj))
		{
			if (e->ny != 0)
			{
				if (e->ny == -1)
				{
					isSimonOnAir = false;
					vy = 0;
				}
				else
				{
					y += dy;
				}
			}
		}
	}
	
	// clean up collision events
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	listObject.clear();
	
}

void CSimon::CollisionWithHidenObject(DWORD dt, vector<LPGAMEOBJECT>& listHidenObj)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	CalcPotentialCollisions(&listHidenObj, coEvents);
	if (coEvents.size() > 0)
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(e->obj);// if e->obj is torch 

			if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE
				|| hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW
				|| hidenObj->GetState() == HIDENOBJECT_TYPE_SPECIAL)
			{
				if (isBeingOnStair)
				{
					isBeingOnStair = false;
					DebugOut(L"Ket thuc thang\n");
					state = ANI_SIMON_IDLE;
				}
			}
		}

	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CSimon::CollisionWithPlatform(DWORD dt, LPGAMEOBJECT plf, float min_tx, float min_ty, int nx, int ny, float rdx, float rdy)
{
	y += min_ty * dy + ny * 0.4f;
	

	vx += plf->Getvx();
	if (vx > plf->Getvx())
		vx -= plf->Getvx();
	dx = vx * dt;


	if (ny == -1)
	{
		isSimonOnAir = false;
		this->vy = GRAVITY * dt;
		x += dx;
	}	

		
}

void CSimon::CollisionWithEnemy(DWORD dt,vector<LPGAMEOBJECT>& listObj)
{

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
		
	// turn off collision when die 
	if(state!=STATE_SIMON_DIE&& untouchable == 0&&!isBeingOnStair)
		CalcPotentialCollisions(&listObj, coEvents);
	if (coEvents.size() > 0)
	{
		float min_tx, min_ty, nx0 = 0, ny0;
		float rdx = 0;
		float rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx0, ny0, rdx, rdy);

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (e->obj->GetState() == STATE_ENEMY_EXIST)
			{
				this->nx = -nx0;

				vx = nx0 * SIMON_WALKING_SPEED;
				vy = -SIMON_JUMP_SPEED_Y;

				CGameObject::Update(dt);

				x += dx;
				y += dy;

				this->blood -= 2;

				StartUntouchable();
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CSimon::CollisionWithObjectHaveItem(DWORD dt, vector<LPGAMEOBJECT>& listObj)
{
	RECT rect1, rect2;

	float l1, t1, r1, b1;
	float l2, t2, r2, b2;
	// Get bounding box of knife
	GetBoundingBox(l1, t1, r1, b1);
	rect1.left = (int)l1;
	rect1.top = (int)t1;
	rect1.right = (int)r1;
	rect1.bottom = (int)b1;

	vector<LPGAMEOBJECT> listItem;

	for (UINT i = 0;i < listObj.size();i++)
	{
		if (dynamic_cast<CTorch*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == STATE_TORCH_ITEM_EXIST)
			{
				listObj.at(i)->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					CTorch* torch = dynamic_cast<CTorch*>(listObj.at(i));
					CItem* item = dynamic_cast<CItem*>(torch->GetItem());

					listItem.push_back(item);
					torch->SetState(STATE_TORCH_ITEM_NOT_EXIST);	// item was eated => k render item nữa
				}
			}
		}
		else if ( dynamic_cast<CCandle*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == STATE_TORCH_ITEM_EXIST)
			{
				listObj.at(i)->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					CCandle* candle = dynamic_cast<CCandle*>(listObj.at(i));
					CItem* item = dynamic_cast<CItem*>(candle->GetItem());

					listItem.push_back(item);
					candle->SetState(STATE_TORCH_ITEM_NOT_EXIST);	// item was eated => k render item nữa
				}
			}
		}
		else if (dynamic_cast<CEnemy*>(listObj.at(i)))
		{
			if (listObj.at(i)->GetState() == STATE_ENEMY_ITEM_EXIST)
			{
				listObj.at(i)->GetBoundingBox(l2, t2, r2, b2);
				rect2.left = (int)l2;
				rect2.top = (int)t2;
				rect2.right = (int)r2;
				rect2.bottom = (int)b2;
				if (CGame::GetInstance()->isCollision(rect1, rect2)) // => có đụng độ
				{
					CEnemy* enemy = dynamic_cast<CEnemy*>(listObj.at(i));
					CItem* item = dynamic_cast<CItem*>(enemy->GetItem());

					listItem.push_back(item);
					enemy->SetState(STATE_TORCH_ITEM_NOT_EXIST);	// item was eated => k render item nữa
				}
			}
		}
		else if (dynamic_cast<CBreakBrick*>(listObj.at(i)))
		{
		}
	}
	CollisionWithItem(listItem);
	listItem.clear();
}

void CSimon::GetBoundingBox(float &left, float &top, float &right, float &bottom)
{
	//CGame *game = CGame::GetInstance();
	left = this->x;
	top = this->y;
	right = this->x + SIMON_WIDTH;

	if (state == STATE_SIMON_DIE)
	{
		right = this->x + SIMON_WIDTH_DIE;
		bottom = this->y + SIMON_HEIGHT_DIE;
	}
	else if (state == STATE_SIMON_SIT 
		|| state == STATE_SIMON_SIT_ATTACK 
		||(animations[ANI_SIMON_JUMPING]->GetCurrentFrame() > 0))
		//|| (state == STATE_SIMON_GO_UP && state == STATE_SIMON_GO_DOWN))
	{
		if(state!=STATE_SIMON_UP)
			bottom = this->y + SIMON_HEIGHT_SIT;
	}
	else
		bottom = this->y + SIMON_HEIGHT_STAND;
}

void CSimon::IsCanOnStair(vector<LPGAMEOBJECT>& listObj)
{
	CGame* game = CGame::GetInstance();
	RECT rect, rect1;
	float l, t, r, b;
	float l1, t1, r1, b1;

	GetBoundingBox(l, t, r, b);
	rect.left = (int)l;
	rect.top = (int)t;
	rect.right = (int)r;
	rect.bottom = (int)b;

	for (int i = 0; i < listObj.size(); i++)
	{

		if (listObj.at(i)->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE 
			|| listObj.at(i)->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW
			|| listObj.at(i)->GetState() == HIDENOBJECT_TYPE_SPECIAL)
		{
			listObj.at(i)->GetBoundingBox(l1, t1, r1, b1);
			rect1.left = (int)l1;
			rect1.top = (int)t1;
			rect1.right = (int)r1;
			rect1.bottom = (int)b1;
			if (CGame::GetInstance()->isCollision(rect, rect1)) // đụng độ
			{
				//DebugOut(L"Va cham doi tuong thang binh thuong\n");
				CHidenObject* hidenObj = dynamic_cast<CHidenObject*>(listObj.at(i));
				// xác định hướng của stair
				if (hidenObj->getNx() * hidenObj->getNy() > 0)
				{
					_stairTrend = 1;	// right
				}
				else
				{
					_stairTrend = -1;	// left
				}
				auto_x = hidenObj->GetAutoX();
				if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_ABOVE)
				{
					isCanOnStair = -1;
					game = NULL;
					return;
				}
				if (hidenObj->GetState() == HIDENOBJECT_TYPE_STAIR_BELOW)
				{
					isCanOnStair = 1;
					game = NULL;
					return;
				}
				if (hidenObj->GetState() == HIDENOBJECT_TYPE_SPECIAL)
				{
					if (isGoDown)
					{
						_stairTrend = 1;
						isCanOnStair = -1;
					}
					if (isGoUp)
					{
						_stairTrend = -1;
						isCanOnStair = 1;
					}
					game = NULL;
					return;
				}
			}
		}
	}

	isGoDown = false;
	isGoUp = false;
	auto_x = -1;
	isCanOnStair = 0;
	game = NULL;
	return;
}

void CSimon::CalculateAutoGo()
{
	if (auto_x < x)
	{
		nx = -1;
	}
	else if (auto_x > x)
	{
		nx = 1;
	}
}

void CSimon::LoadSubWeapon(int subwp)
{
	int IDSubWeaponInVector;
	switch (subwp)
	{
	case eType::WEAPON_KNIFE:
	{
		IDSubWeaponInVector = ID_SUB_WEAPON_IN_SIMON_KNIFE;
	}
	break;
	case eType::WEAPON_AXE:
	{
		IDSubWeaponInVector = ID_SUB_WEAPON_IN_SIMON_AXE;
	}
	break;
	case eType::WEAPON_BOOMERANG:
	{
		IDSubWeaponInVector = ID_SUB_WEAPON_IN_SIMON_BOOMERANG;
	}
	break;
	case eType::WEAPON_HOLLYWATER:
	{
		IDSubWeaponInVector = ID_SUB_WEAPON_IN_SIMON_HOLLYWATER;
	}
	break;
	}
	if (listSubWeapon[IDSubWeaponInVector]->GetState() == STATE_SUBWEAPON_HIDE)
	{
		listSubWeapon[IDSubWeaponInVector]->SetTrend(nx);
		listSubWeapon[IDSubWeaponInVector]->SetState(STATE_SUBWEAPON_APPEAR);
		listSubWeapon[IDSubWeaponInVector]->SetPosition(this->x, this->y);
	}
}