#include "pch.h"
#include "CamerActor.h"
#include "Game.h"
#include "Renderer.h"
#include "MoveComponent.h"

CamerActor::CamerActor(Game* game):
	Actor(game)
{
	MoveComponent *mv = new MoveComponent(this);
	mv->SetAngularSpeed(-Math::Pi); 
}

void CamerActor::CustomUpdate(float deltaTime)
{
	Vector3 eye = GetPosition(); 
	Vector3 target = GetForward() * 100.0f; 
	Vector3 up = Vector3::UnitZ; 

	Matrix4 view = Matrix4::CreateLookAt(eye , target , up);
	GetGame()->GetRenderer()->SetView(view); 
}

CamerActor::~CamerActor()
{
}
