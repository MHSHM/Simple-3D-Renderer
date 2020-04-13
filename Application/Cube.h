#pragma once
#include "Actor.h"
#include "Math.h"
class Cube :public Actor
{
public:
	Cube(class Game* game , float scale , Vector3 pos , Quaternion rotation);
	~Cube();
};

