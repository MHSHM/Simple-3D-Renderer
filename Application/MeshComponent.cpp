#include "pch.h"
#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include <vector>
#include "Shader.h"

MeshComponent::MeshComponent(Actor *owner) :
	Component(owner),
	mMesh(nullptr)
{
}

void MeshComponent::SetMeshCompToShader() 
{
	Renderer* renderer = mOwner->GetGame()->GetRenderer();
	renderer->GetDrawElements()[renderer->GetShadersByName()[mMesh->GetShaderName()]].emplace_back(this); 
}

MeshComponent::~MeshComponent()
{
}
