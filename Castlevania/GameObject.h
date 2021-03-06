﻿#pragma once
#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_


#include <Windows.h>
#include <d3dx9.h>
#include <vector>
#include <algorithm>

#include "Sprites.h"
#include"Animation.h"


using namespace std;

#define ID_TEX_BBOX -100		// special texture to draw object bounding box

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;
struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;		// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}
};



class CGameObject
{
public:

	float x;
	float y;

	float dx;	// dx = vx*dt
	float dy;	// dy = vy*dt

	float vx;
	float vy;

	int nx;

	int state;

	DWORD dt;

	int blood;
	int type;

	//bool isOnCamera;

	vector<LPANIMATION> animations;
	LPANIMATION animation;

public:
	virtual void SetPosition(float x, float y) { this->x = x, this->y = y; }
	D3DXVECTOR2 GetPositionVector2(D3DXVECTOR2 &vt) 
	{
		vt.x = this->x;
		vt.y = this->y;
		return vt;
	}

	void SetSpeed(float vx, float vy) { this->vx = vx, this->vy = vy; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx; vy = this->vy; }

	void SetTrend(int nx) { this->nx = nx; }

	int GetState() { return this->state; }

	virtual int getType() { return type; };

	void RenderBoundingBox();

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);// cài đặt tổng quát hơn AABB(chỉ xét 1 static 1 move)
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents);//lọc ra các đối tượng có khả năng collision
	void FilterCollision(//lựa 2 vật thể va chạm
		vector<LPCOLLISIONEVENT>& coEvents,
		vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	// tính toán khoảng cách dựa vào 2 điểm
	float CalculateDistance(D3DXVECTOR2 obj1, D3DXVECTOR2 obj2);

	// không dùng animation_set nên sẽ dùng anmation theo hướng demo 4
	void AddAnimation(int aniId); // push back ID vào phần vector LPANIMATION

	CGameObject(float _x = 0, float _y = 0,int _type=0);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;// bounding box mỗi object mỗi khác, tùy thuộc vào từng trạng thái
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	float Getvx() { return vx; }
	float Getvy() { return vy; }

	int GetBlood() { return blood; }
	virtual void Hurt() { blood -=1; }

	void ClearAnimations()		// cần cảnh giác
	{
		animations.clear();
	}
	~CGameObject();
};


#endif