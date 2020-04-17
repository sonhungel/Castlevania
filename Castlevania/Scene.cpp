#include "Scene.h"

CScene::CScene(int id)
{
	this->id = id;
}


void CScene::LoadResoure()
{
	CManagementTexture* manage = new CManagementTexture();
	objects.clear();
	
	map = new CMap();
	map->LoadMap();


	simon = CSimon::GetInstance();
	simon->SetPosition(0.0f, 20.0f);
	objects.push_back(simon);


	CTorch* torch0 = new CTorch();
	torch0->SetPosition(190, 300);
	objects.push_back(torch0);

	CTorch* torch1 = new CTorch();
	torch1->SetPosition(416, 300);
	objects.push_back(torch1);

	CTorch* torch2 = new CTorch();
	torch2->SetPosition(640, 300);
	objects.push_back(torch2);

	CTorch* torch3 = new CTorch();
	torch3->SetPosition(864, 300);
	objects.push_back(torch3);


	for (int i = 0; i < 96; i++)
	{
		CBrick* brick = new CBrick();
		brick->SetPosition(i * 32, 360);
		objects.push_back(brick);
	}
	
}

void CScene::Update(DWORD dt)
{
	float cx, cy;
	simon->GetPosition(cx, cy);


	vector<LPGAMEOBJECT> coObjects;
	for (int i = 1; i < objects.size(); i++)
	{
		coObjects.push_back(objects[i]);
	}

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update(dt, &coObjects);
	}

	// Update camera to follow simon

	cx -= SCREEN_WIDTH / 2 - 40;
	cy -= SCREEN_HEIGHT / 2;
	if (cx < 0) cx = 0; if (cx > 966) cx = 966;

	game = CGame::GetInstance();
	game->SetCamPos(cx, 0);
}
void CScene::Render()
{
	map->DrawMap();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}
