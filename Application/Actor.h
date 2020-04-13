#pragma once
#include "Math.h"
#include <vector>
#include <SDL.h>
class Actor
{
public:
	Actor(class Game *game);
	virtual ~Actor();

	virtual void CustomUpdate(float deltaTime) {};
	void Update(float deltaTime); 
	void UpdateComponents(float deltaTime); 

	void AddComponent(class Component *component); 
	void RemoveComponent(class Component *component);

	void ComputeWorldTransform();

	void SetScale(float val) { mScale = val, mRecomputeWorldTransform = true;  }
	void SetPosition(Vector3 val) { mPosition = val, mRecomputeWorldTransform = true;  }
	void SetRotation(Quaternion val) { mRotation = val, mRecomputeWorldTransform = true;  }

	float GetScale() const { return mScale;  }
	Vector3& GetPosition() { return mPosition;  }
	Quaternion GetRotation() { return mRotation;  }
	const Matrix4& GetWorldTransform() const { return mTransformMatrix;  }
	Vector3 GetForward() const { return Vector3::Transform(Vector3::UnitX, mRotation); }


	class Game* GetGame() { return game; }

private:
	float mScale;
	Vector3 mPosition; 
	Quaternion mRotation;

	std::vector<class Component*> mComponents; 

	Matrix4 mTransformMatrix; 
	bool mRecomputeWorldTransform; 


	class Game *game; 
};

