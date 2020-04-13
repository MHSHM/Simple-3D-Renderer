#pragma once
#include "Actor.h"
#include "Math.h"
class CamerActor : public Actor
{
public:
	CamerActor(class Game* game);
	~CamerActor();

	void CustomUpdate(float deltaTime) override; 
};

