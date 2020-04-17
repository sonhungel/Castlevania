#include "MagagementTexture.h"
#include "Simon.h"
#include "Brick.h"


CManagementTexture::CManagementTexture()
{
	CTextures* textures = CTextures::GetInstance();

	textures->Add(ID_TEX_SIMON, L"simon\\simon.png", D3DCOLOR_XRGB(255, 0, 255));
	//textures->Add(ID_TEX_SIMON_TRANS, L"simon\\simon_trans.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_MAP, L"map\\map.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_GROUND, L"map\\ground.png", D3DCOLOR_XRGB(0, 0, 0));
	textures->Add(ID_TEX_TORCH, L"map\\torch.png", D3DCOLOR_XRGB(255, 0, 255));
	textures->Add(ID_TEX_TORCH_FIRE, L"item\\Torch_fire.png", D3DCOLOR_XRGB(255, 0, 255));

	CSprites* sprites = CSprites::GetInstance();
	CAnimations* animations = CAnimations::GetInstance();

	LPDIRECT3DTEXTURE9 texmap = textures->Get(ID_TEX_MAP);

	ifstream inFile("texture/sprites.txt");

	// If the file opened correctly then call load methods
	while (inFile)
	{
		CSprite* sprite = new CSprite();
		sprite->load(inFile);
		sprites->Add(sprite);
	}



#pragma region add sprites Simon 

	LPANIMATION ani;

	ani = new CAnimation(100); //simon idle left
	ani->Add(10004);
	animations->Add(400, ani);

	ani = new CAnimation(1); //simon trans idle left
	ani->Add(10400);
	ani->Add(10004);
	animations->Add(410, ani);

	ani = new CAnimation(100);// simon walk left
	ani->Add(10011);
	ani->Add(10012);
	// ani->Add(10013); // Thêm 1 frame để simon di chuyển mượt hơn
	animations->Add(401, ani);

	ani = new CAnimation(100);// simon jump left
	ani->Add(10201);
	animations->Add(402, ani);

	ani = new CAnimation(100);// simon sit left
	ani->Add(10201);
	animations->Add(403, ani);

	ani = new CAnimation(100);// simon stand attack
	ani->Add(10300);
	ani->Add(10301);
	ani->Add(10302);
	animations->Add(404, ani);

	ani = new CAnimation(100);//simon sit attack
	ani->Add(10310);
	ani->Add(10311);
	ani->Add(10312);
	animations->Add(405, ani);


#pragma endregion

#pragma region Add sprites Map
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			sprites->Add(index++, j * 64, i * 64, j * 64 + 64, i * 64 + 64, texmap);
		}
	}

#pragma endregion

#pragma region Add sprites Ground
	ani = new CAnimation(100);
	ani->Add(10000);
	animations->Add(500, ani);


#pragma endregion

#pragma region Add sprites Torch 


	ani = new CAnimation(100);
	ani->Add(11000);
	ani->Add(11001);
	animations->Add(501, ani); // torch


#pragma endregion

#pragma region Add sprites fire after torch not exsist
	ani = new CAnimation(100);

	ani->Add(14002);
	ani->Add(14001);
	ani->Add(14000);
	animations->Add(800, ani); // fire after torch not exsist
#pragma endregion

}