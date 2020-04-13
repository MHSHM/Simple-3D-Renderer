#include "pch.h"
#include "Renderer.h"
#include "Game.h"
#include "Actor.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "Texture.h"

Renderer::Renderer(Game *game):
	game(game)
{
}


bool Renderer::Initialize(int width , int height) 
{

	mWidth = width; 
	mHeight = height; 

	// Use the core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Specify version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("3D Renderer", 100, 100, mWidth, mHeight, SDL_WINDOW_OPENGL); 
	if (!mWindow) 
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mContext = SDL_GL_CreateContext(mWindow); 

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	glGetError();
	
	if (!LoadShaders()) 
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}
	
	return true; 
}

void Renderer::Unload()
{
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::ShutDown() 
{
	for (auto shader : mShaders) 
	{
		shader->Unload(); 
	}
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
}

void Renderer::Draw() 
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);


	for (auto shader : mShaders) 
	{
		shader->Bind(); 
		for (int i = 0; i < (int)drawElements[shader].size(); ++i) 
		{
			// Get Target World Transform Matrix
			Matrix4 worldTransform = drawElements[shader][i]->GetOwner()->GetWorldTransform(); 
			
			// Get Target Mesh
			Mesh *mesh = drawElements[shader][i]->GetMesh();
			
			// Setting Uniforms
			shader->SetMatrixUniform("mWorldTransform", worldTransform);  
			shader->SetFloatUniform("mAmbientStrength" , mesh->GetAmbientStrength());
			shader->SetFloatUniform("mSpecularPower", mesh->GetSpecularPower()); 
			SetLightUniforms(shader);

			// Activate Texture
			Texture *texture = GetTexture(mesh->GetTexturePath());
			if (texture)
			{
				texture->Bind();
			}

			// Activate Vertex Array
			mesh->GetVertexArray()->Bind(); 

			// Draw Call
			glDrawElements(GL_TRIANGLES, mesh->GetVertexArray()->GetIndexBufferSize(), GL_UNSIGNED_INT, nullptr);
		}
	}
	
	SDL_GL_SwapWindow(mWindow);
}

bool Renderer::LoadShaders() 
{
	// Load Basic Shader
	Shader *basicShader = new Shader(this); 
	bool isLoaded = basicShader->Load("Shaders/BasicShader.vert", "Shaders/BasicShader.frag");
	if (!isLoaded) 
	{
		return false; 
	}
	mShadersByName["BasicShader"] = basicShader;
	basicShader->Bind();
	mView = Matrix4::CreateLookAt(Vector3::Zero, Vector3::UnitX, Vector3::UnitZ);
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(70.0f),
		static_cast<float>(mWidth), static_cast<float>(mHeight), 25.0f, 10000.0f);
	basicShader->SetMatrixUniform("mViewProjection" , mView * mProjection);

	// Load Phong Shader
	Shader *phongShader = new Shader(this); 
	isLoaded = false; 
	isLoaded = phongShader->Load("Shaders/Phong.vert", "Shaders/Phong.frag"); 
	mShadersByName["Phong"] = phongShader;
	phongShader->Bind(); 
	phongShader->SetMatrixUniform("mViewProjection", mView * mProjection); 
	return true; 
}

Mesh* Renderer::GetMesh(std::string path) 
{
	auto iter = mMeshes.find(path);
	if (iter != mMeshes.end()) 
	{
		return iter->second; 
	}

	Mesh *mesh = new Mesh(); 
	bool isLoaded = mesh->Load(path , this); 
	if (!isLoaded) 
	{
		delete mesh; 
		return nullptr; 
	}

	mMeshes.emplace(path , mesh); 
	return mesh; 
}


Texture* Renderer::GetTexture(std::string path) 
{
	auto iter = mTextures.find(path); 
	if (iter != mTextures.end()) 
	{
		return iter->second; 
	}

	Texture *t = new Texture(); 
	bool isLoaded = t->Load(path);
	if (!isLoaded) 
	{
		delete t; 
		return nullptr; 
	}
	mTextures.emplace(path, t); 
	return t; 
}

void Renderer::SetLightUniforms(Shader* shader) 
{
	shader->SetVectorUniform("mLightSource", mLightSource); 
	shader->SetVectorUniform("mLightColor" , mLightColor); 
	shader->SetVectorUniform("mViewPosition", Vector3(0.0f, 0.0f, 0.0f)); 
}

Renderer::~Renderer()
{
}
