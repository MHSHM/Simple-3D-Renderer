#pragma once
#include "Actor.h"
#include "Math.h"
class Shpere :public Actor
{
public:
	Shpere(class Game* game , float scale , Vector3 position , Quaternion rotation);
	~Shpere();
};

