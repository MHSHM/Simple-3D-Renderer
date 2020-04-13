#include "pch.h"
#include "MoveComponent.h"
#include "Actor.h"

MoveComponent::MoveComponent(Actor* owner):
	Component(owner),
	mAngularSpeed(0.0f)
{
}

void MoveComponent::Update(float deltaTime)
{
	if (!Math::NearZero(mAngularSpeed)) 
	{
		Quaternion q = mOwner->GetRotation();
		float angle = mAngularSpeed * deltaTime; 
		Quaternion newQ(Vector3::UnitZ , angle);
		q = Quaternion::Concatenate(q , newQ);
		mOwner->SetRotation(q); 
	}
}

MoveComponent::~MoveComponent()
{
}
