#pragma once
#ifndef __PORTAL_H_
#define __PORTAL_H_

#include "GameObject.h"

#define PORTAL_WIDTH 20
#define PORTAL_HEIGHT 20
class CPortal : public CGameObject
{
	int scene_id;	// target scene to switch to 

public:
	CPortal(int scene_id);
	void Render();
	void GetBoundingBox(float &left, float &top, float &right, float &bottom);
	int GetSceneId() { return scene_id;  }
};
#endif