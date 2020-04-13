#pragma once
#include "Component.h"
#include "Math.h"
class MoveComponent : public Component
{
public:
	MoveComponent(class Actor* owner);
	~MoveComponent();

	void Update(float deltaTime) override; 
	void SetAngularSpeed(float val) { mAngularSpeed = val;  }

private:
	float mAngularSpeed; 

};

