#include "MapTexture.h"
#include "Simon.h"
#include "Brick.h"
#include"Whip.h"


	CMapTexture::CMapTexture(int id)
	{
		CTextures* textures = CTextures::GetInstance();

		textures->Add(ID_TEX_MAP, L"map\\map.png", D3DCOLOR_XRGB(255, 0, 255));


		CSprites* sprites = CSprites::GetInstance();
		CAnimations* animations = CAnimations::GetInstance();

		LPDIRECT3DTEXTURE9 texmap = textures->Get(ID_TEX_MAP);

		int index = 0;
		if (id = 1)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					sprites->Add(index++, j * 64, i * 64, j * 64 + 64, i * 64 + 64, texmap);
				}
			}
		}
	}
