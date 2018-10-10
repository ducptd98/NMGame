#pragma once
#include "DrawableObject.h"

class Number : public DrawableObject
{
public:
	void next(int& curFrame);
	void draw();
	void updateLocation();

	Number();
	~Number();
};

