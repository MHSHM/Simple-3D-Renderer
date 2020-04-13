#include "pch.h"
#include "Actor.h"
#include "Game.h"
#include "Math.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game *game) :
	game(game),
	mScale(1.0f),
	mPosition(Vector3::Zero),
	mRotation(Quaternion::Identity),
	mRecomputeWorldTransform(true)
{
	GetGame()->AddActor(this); 
}


void Actor::Update(float deltaTime) 
{
	UpdateComponents(deltaTime);
	CustomUpdate(deltaTime); 
	ComputeWorldTransform();
}

void Actor::UpdateComponents(float deltaTime) 
{
	for (auto comp : mComponents) 
	{
		comp->Update(deltaTime); 
	}
}

void Actor::ComputeWorldTransform() 
{
	if (mRecomputeWorldTransform) 
	{
		mRecomputeWorldTransform = false; 
		mTransformMatrix = Matrix4::CreateScale(mScale); 
		mTransformMatrix *= Matrix4::CreateFromQuaternion(mRotation); 
		mTransformMatrix *= Matrix4::CreateTranslation(mPosition); 
	}
}




void Actor::AddComponent(Component *component) 
{
	mComponents.emplace_back(component); 
}

void Actor::RemoveComponent(Component* component) 
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component); 
	if (iter != mComponents.end()) 
	{
		std::iter_swap(iter, mComponents.end() - 1); 
		mComponents.pop_back(); 
	}
}


Actor::~Actor()
{
	GetGame()->RemoveActor(this); 
	while (!mComponents.empty()) 
	{
		delete mComponents.back(); 
	}
}
