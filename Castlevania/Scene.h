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

#include "Brick.h"


#define SCREEN_WIDTH 560
#define SCREEN_HEIGHT 460


class CScene
{
	CSimon* simon;
	//CMap* map;

	CGame* game;
	vector<LPGAMEOBJECT> objects;
	int id;
public:
	CScene(int id = 0);
	void LoadResoure();
	void Update(DWORD dt);
	void Render();

};
#endif