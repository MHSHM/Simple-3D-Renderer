#include "pch.h"
#include "Cube.h"
#include "Game.h"
#include "Renderer.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "MoveComponent.h"

Cube::Cube(Game *game , float scale, Vector3 pos, Quaternion rotation):
	Actor(game)
{
	SetScale(scale);
	SetPosition(pos);
	SetRotation(rotation); 
	
	MeshComponent *mc = new MeshComponent(this);
	mc->SetMesh(game->GetRenderer()->GetMesh("Assets/Cube.gpmesh")); 
	mc->SetMeshCompToShader(); 

	MoveComponent* mv = new MoveComponent(this);
	mv->SetAngularSpeed(1.0); 

}


Cube::~Cube()
{
}
