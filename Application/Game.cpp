#include "pch.h"
#include "Game.h"
#include <algorithm>
#include "Renderer.h"
#include "Actor.h"
#include "Cube.h"
#include "Shpere.h"

Game::Game():
	mIsRunning(true),
	mTicksCount(0)
{
}

bool Game::Initialize() 
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer = new Renderer(this); 
	if (!mRenderer->Initialize(1024,768)) 
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer->SetLightSource(Vector3(0.0f, 0.0f, 50.0f)); 
	mRenderer->SetLightColor(Vector3(0.0f, 0.8f, 0.3f)); 

	mTicksCount = SDL_GetTicks(); 

	LoadData(); 

	return true; 
}

void Game::RunGame() 
{
	while (mIsRunning) 
	{
		ProcessInput(); 
		UpdateGame(); 
		GenerateOutput(); 
	}
}


void Game::ProcessInput() 
{
	SDL_Event event; 
	while (SDL_PollEvent(&event)) 
	{
		if (event.type == SDL_QUIT) 
		{
			mIsRunning = false; 
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE])
	{
		mIsRunning = false;
	}
}

void Game::UpdateGame() 
{
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	if (deltaTime > 0.05f) 
	{
		deltaTime = 0.05f; 
	}
	mTicksCount = SDL_GetTicks();

	for (auto actor : mActors) 
	{
		actor->Update(deltaTime); 
	}
}

void Game::AddActor(Actor* actor) 
{
	mActors.emplace_back(actor); 
}

void Game::RemoveActor(Actor *actor) 
{
	auto iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end()) 
	{
		std::iter_swap(iter, mActors.end() - 1); 
		mActors.pop_back(); 
	}
	
}

void Game::GenerateOutput() 
{
	mRenderer->Draw(); 
}

void Game::LoadData() 
{
	Quaternion q(Vector3::UnitY, -Math::PiOver2);
	q = Quaternion::Concatenate(q, Quaternion(Vector3::UnitZ, Math::Pi));
	Cube *cube = new Cube(this, 100.0f, Vector3(300.0f, 100.0f, 0.0f), q);

	Shpere *sp = new Shpere(this , 5.0f , Vector3(300.0f , -100.0f , 0.0f) , Quaternion::Identity); 
}

void Game::UnloadData()
{
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	if (mRenderer)
	{
		mRenderer->Unload();
	}
}


void Game::ShutDown()
{
	UnloadData();
	if (mRenderer)
	{
		mRenderer->ShutDown();
	}
	SDL_Quit();
}



Game::~Game()
{
}
