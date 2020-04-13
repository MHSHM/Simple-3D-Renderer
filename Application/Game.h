#pragma once
#include <vector>

class Game
{
public:
	Game();
	~Game();

	bool Initialize(); 
	void RunGame(); 
	void ShutDown();
	void LoadData(); 
	void UnloadData(); 

	void AddActor(class Actor* actor); 
	void RemoveActor(class Actor *actor);

	class Renderer *GetRenderer() { return mRenderer;  }

private:

	void ProcessInput(); 
	void UpdateGame(); 
	void GenerateOutput(); 

	std::vector<class Actor*> mActors; 

	bool mIsRunning; 

	int mTicksCount; 

	class Renderer *mRenderer; 
};

