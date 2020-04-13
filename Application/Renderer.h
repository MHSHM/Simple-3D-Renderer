#pragma once
#define GLEW_STATIC
#include <SDL.h>
#include <GL/glew.h>
#include "Math.h"
#include <unordered_map>
#include <vector>

class Renderer
{
public:
	Renderer(class Game* game);
	~Renderer();

	bool Initialize(int width , int height);
	void ShutDown(); 
	void Unload(); 

	void Draw(); 

	bool LoadShaders();

	std::vector<class Shader*>& GetShaders() { return mShaders;  }
	std::unordered_map<std::string, class Shader*>& GetShadersByName() { return mShadersByName;  }
	std::unordered_map<class Shader*, std::vector<class MeshComponent*> >& GetDrawElements() { return drawElements;  }


	class Mesh* GetMesh(std::string path); 
	class Texture* GetTexture(std::string path); 

	void SetView(Matrix4 view) { mView = view;  }

	void SetLightSource(Vector3 val) { mLightSource = val;  }
	void SetLightColor(Vector3 val) { mLightColor = val; }
	void SetLightUniforms(class Shader* shader); 


private:

	
	int mWidth;
	int mHeight;

	SDL_Window *mWindow;
	SDL_GLContext mContext;

	Matrix4 mView; 
	Matrix4 mProjection; 

	class Game *game;

	// Shaders Stuff
	std::vector<class Shader*> mShaders;
	std::unordered_map<std::string , class Shader*> mShadersByName; 
	std::unordered_map<class Shader*, std::vector<class MeshComponent*> > drawElements; 


	// Meshes Stuff
	std::unordered_map<std::string , class Mesh*> mMeshes; 

	//Texture Stuff
	std::unordered_map<std::string, class Texture*> mTextures; 

	//Lighting Stuff
	Vector3 mLightSource; 
	Vector3 mLightColor; 
};

