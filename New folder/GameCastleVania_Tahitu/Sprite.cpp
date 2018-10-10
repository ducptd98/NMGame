#include "Sprite.h"

Sprite::Sprite(const char* imgFilePath, const char* animationInfoFilePath)
{
	init(imgFilePath, animationInfoFilePath);
}

void Sprite::init(const char * imgFilePath, const char * animationInfoFilePath)
{
	int r, g, b;
	fstream fs(animationInfoFilePath);

	fs >> r >> g >> b >> nAnimation;

	animates = new Animate[nAnimation];

	for (int i = 0; i < nAnimation; i++)
		animates[i].init(fs);
	image = new Texture(imgFilePath, D3DCOLOR_XRGB(r, g, b));
}

void Sprite::initAnimation(const char * animationInfoFilePath)
{
	int r, g, b;
	fstream fs(animationInfoFilePath);

	fs >> r >> g >> b >> nAnimation;

	animates = new Animate[nAnimation];

	for (int i = 0; i < nAnimation; i++)
		animates[i].init(fs);
}

void Sprite::draw(int x, int y, int curAnimate, int curFrame)
{
	Animate* animate = &animates[curAnimate];
	image->RenderTexture(x, y, &animate->frames[curFrame].toRECT());
}

Sprite::Sprite()
{
}

Sprite::~Sprite()
{
}
