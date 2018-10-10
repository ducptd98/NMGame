#include "Texture.h"

Texture::Texture(const char* filepath, D3DCOLOR transColor)
{
	Init(filepath, transColor);
}

void Texture::Init(const char* filepath, D3DCOLOR transColor)
{
	direction = Left;
	HRESULT result;
	D3DXIMAGE_INFO info;
	result = D3DXGetImageInfoFromFile(filepath, &info);
	Width = info.Width;
	Height = info.Height;
	if (result != D3D_OK)
		return;

	result = D3DXCreateTextureFromFileEx(
		GRAPHICS->GetDevice(),
		filepath,
		info.Width,
		info.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transColor,
		&info,
		NULL,
		&m_image);

	if (result != D3D_OK)
		return;
}

void Texture::RenderTexture(int x, int y, RECT *r)
{
	GRAPHICS->GetSprite()->Draw(m_image,
		r,
		0,
		&D3DXVECTOR3(x, y, 0),
		D3DCOLOR_XRGB(255, 255, 255));
}

Texture::Texture()
{
}

Texture::~Texture()
{
	if (m_image)
	{
		m_image->Release();
		m_image = 0;
	}
}
