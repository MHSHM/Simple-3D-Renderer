#pragma once
#include "Component.h"
class MeshComponent : public Component
{
public:
	MeshComponent(class Actor* owner);
	~MeshComponent();

	void SetMesh(class Mesh* mesh) { mMesh = mesh;  }
	class Actor* GetOwner() { return mOwner;  }

	class Mesh* GetMesh() { return mMesh;  }

	void SetMeshCompToShader(); 

private:
	class Mesh* mMesh; 
};

