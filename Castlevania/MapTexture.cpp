#include "MapTexture.h"
#include "Simon.h"
#include "Brick.h"
#include"Whip.h"

#define ID_SCENE_MAP_1	1
#define ID_SCENE_MAP_2	2
#define ID_SCENE_MAP_3	3
#define ID_SCENE_MAP_4	4
#define ID_SCENE_MAP_5	5
#define ID_SCENE_MAP_6	6

	CMapTexture::CMapTexture(int id)
	{
		CTextures* textures = CTextures::GetInstance();

		textures->Add(ID_TEX_MAP1, L"map\\map.png", D3DCOLOR_XRGB(255, 0, 255));
		textures->Add(ID_TEX_MAP2, L"map\\Scene21.png", D3DCOLOR_XRGB(255, 0, 255));
		textures->Add(ID_TEX_MAP3, L"map\\Scene22.png", D3DCOLOR_XRGB(255, 0, 255));

		CSprites* sprites = CSprites::GetInstance();
		CAnimations* animations = CAnimations::GetInstance();

		
		
		if(id==ID_SCENE_MAP_1)
		{
			LPDIRECT3DTEXTURE9 texmap = textures->Get(ID_TEX_MAP1);
			int index = 0;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					sprites->Add(index++, j * 64, i * 64, j * 64 + 64, i * 64 + 64, texmap);
				}
			}
		}
		if (id == ID_SCENE_MAP_2)
		{
			LPDIRECT3DTEXTURE9 texmap = textures->Get(ID_TEX_MAP2);
			int index = 0;
			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					sprites->Add(index++, j * 64, i * 64, j * 64 + 64, i * 64 + 64, texmap);
				}
			}
		}
		if (id == ID_SCENE_MAP_3)
		{
			LPDIRECT3DTEXTURE9 texmap = textures->Get(ID_TEX_MAP3);
			int index = 0;
			for (int i = 0; i <6 ; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					sprites->Add(index++, j * 63, i * 64, j * 63 + 63, i * 64 + 64, texmap);
				}
			}
		}
		
	}
