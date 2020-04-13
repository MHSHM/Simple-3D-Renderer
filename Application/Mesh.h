#pragma once
#include <string>
#include <vector>
class Mesh
{
public:
	Mesh();
	~Mesh();

	bool Load(std::string path , class Renderer *renderer);
	void Unload(); 

	std::string& GetShaderName() { return mShaderName;  }
	std::string& GetTexturePath() { return mTexturePath;  }
	float GetAmbientStrength() { return mAmbientStrength;  }
	float GetSpecularPower() { return mSpecularPower;  }

	class VertexArray* GetVertexArray() { return mVertexArray;  }

private:
	std::string mShaderName; 
	std::string mTexturePath;
	float mAmbientStrength; 
	float mSpecularPower; 

	class VertexArray *mVertexArray;
};

