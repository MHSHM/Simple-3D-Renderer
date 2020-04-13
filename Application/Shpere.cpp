#include "pch.h"
#include "Shpere.h"
#include "Game.h"
#include "Renderer.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "MoveComponent.h"

Shpere::Shpere(Game* game, float scale, Vector3 position, Quaternion rotation):
	Actor(game)
{
	SetScale(scale); 
	SetPosition(position); 
	SetRotation(rotation); 

	MeshComponent *mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Sphere.gpmesh")); 
	mc->SetMeshCompToShader(); 

	MoveComponent *mv = new MoveComponent(this);
	mv->SetAngularSpeed(1.0f); 

}


Shpere::~Shpere()
{
}
