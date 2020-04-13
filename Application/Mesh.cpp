#include "pch.h"
#include "Mesh.h"
#include "VertexArray.h"
#include <fstream>
#include <sstream>
#include "rapidjson/document.h"
#include <SDL.h>
#include "Math.h"
#include "Renderer.h"
#include "Shader.h"

Mesh::Mesh():
	mVertexArray(nullptr)
{
}


bool Mesh::Load(std::string path , Renderer *renderer) 
{
	std::ifstream file(path); 
	if (!file.is_open()) 
	{
		SDL_Log("File not found: Mesh %s", path.c_str());
		return false; 
	}

	std::stringstream fileStream; 
	fileStream << file.rdbuf(); 
	std::string content = fileStream.str(); 
	rapidjson::StringStream jsonStr(content.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);

	if (!doc.IsObject()) 
	{
		SDL_Log("Mesh %s is not valid json", path.c_str());
		return false;
	}

	// Take Shader Name
	mShaderName = doc["shader"].GetString();

	// Take Specular Power
	mSpecularPower = doc["specularPower"].GetFloat(); 

	//Take Ambient Strength ;
	mAmbientStrength = doc["ambientStrength"].GetFloat(); 

	// Vertex Size
	unsigned int size = 8 ;

	// Take Texture Path
	mTexturePath = doc["texture"].GetString(); 

	rapidjson::Value& vertsJson = doc["vertices"]; 
	if (!vertsJson.IsArray() || vertsJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no vertices", path.c_str());
		return false;
	}

	std::vector<float> vertices; 
	vertices.reserve(size * vertsJson.Size()); 

	for (rapidjson::SizeType i = 0; i < vertsJson.Size(); ++i) 
	{
		rapidjson::Value& vertex = vertsJson[i]; 
		if (!vertex.IsArray() || vertex.Size() != 8)
		{
			SDL_Log("Unexpected vertex format for %s", path.c_str());
			return false;
		}

		Vector3 pos(vertex[0].GetFloat(), vertex[1].GetFloat(), vertex[2].GetFloat());

		for (rapidjson::SizeType i = 0; i < vertex.Size(); ++i) 
		{
			vertices.emplace_back(vertex[i].GetFloat()); 
		}
	}
 
	rapidjson::Value& indJson = doc["indices"];
	if (!indJson.IsArray() || indJson.Size() < 1)
	{
		SDL_Log("Mesh %s has no indices", path.c_str());
		return false;
	}


	std::vector<unsigned int> indices;
	indices.reserve(indJson.Size() * 3);
	for (rapidjson::SizeType i = 0; i < indJson.Size(); ++i) 
	{
		rapidjson::Value &indexBuff = indJson[i]; 
		if (!indexBuff.IsArray() || indexBuff.Size() != 3)
		{
			SDL_Log("Invalid indices for %s", path.c_str());
			return false;
		}
		
		indices.emplace_back(indexBuff[0].GetInt()); 
		indices.emplace_back(indexBuff[1].GetInt()); 
		indices.emplace_back(indexBuff[2].GetInt()); 
	}


	mVertexArray = new VertexArray(vertices.data(), static_cast<unsigned int>(vertices.size()) / size,
		indices.data(), static_cast<unsigned int>(indices.size()));
	return true;

}

void Mesh::Unload() 
{
	delete mVertexArray; 
	mVertexArray = nullptr; 
}

Mesh::~Mesh()
{
}
