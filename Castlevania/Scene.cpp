#include "Scene.h"
#include"ItemHeart.h"

CScene::CScene(int id)
{
	this->id = id;
}


void CScene::LoadResoure()
{
	CManagementTexture* manage = new CManagementTexture();
	objects.clear();
	
	//map = new CMap();
	//map->LoadMap();


	simon = CSimon::GetInstance();
	simon->SetPosition(0.0f, 20.0f);
	objects.push_back(simon);

	//CItemHeart* heart = new CItemHeart();
	//heart->SetPosition(250, 300);
	//objects.push_back(heart);

	CTorch* torch0 = new CTorch(1);
	torch0->SetPosition(190, 296);
	objects.push_back(torch0);

	CTorch* torch1 = new CTorch(2);
	torch1->SetPosition(420, 296);
	objects.push_back(torch1);

	CTorch* torch2 = new CTorch(3);
	torch2->SetPosition(640, 296);
	objects.push_back(torch2);

	CTorch* torch3 = new CTorch(1);
	torch3->SetPosition(870, 296);
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
	//map->DrawMap();

	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
}
