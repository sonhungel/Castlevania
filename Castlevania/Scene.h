#pragma once
#ifndef __SCENE_H_
#define __SCENE_H_

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "fstream"

#include "debug.h"
#include "Game.h"
#include "GameObject.h"
#include "Textures.h"
#include "MagagementTexture.h"

#include "Simon.h"
#include "Map.h"
#include "Torch.h"
#include"Knife.h"
#include "Brick.h"


#define SCREEN_WIDTH 560
#define SCREEN_HEIGHT 460


class CScene
{
	CSimon* simon;
	CMap* map;
	CKnife* knife;
	CGame* game;
	vector<LPGAMEOBJECT> objects;
public:
	
	void LoadResoure();
	void Update(DWORD dt);
	void Render();

};
#endif