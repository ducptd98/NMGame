#pragma once
#include "Graphics.h"

enum Direction
{
	Left = -1,
	Right = 1
};

class Texture
{
private:
	LPDIRECT3DTEXTURE9 m_image;

public:
	int Width, Height;
	Direction direction;

	Texture(const char* filepath, D3DCOLOR transColor);
	void Init(const char* filepath, D3DCOLOR transColor);
	void RenderTexture(int x, int y, RECT *r);

	Texture();
	~Texture();
};
