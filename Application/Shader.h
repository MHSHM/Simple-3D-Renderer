#pragma once
#include <string>
#include "Math.h"
#include <GL/glew.h>
#include <SDL.h>
class Shader
{
public:
	Shader(class Renderer *renderer);
	~Shader();
 
	bool Load(std::string vertPath , std::string FragPath);
	bool Compile(std::string path, GLenum type , GLuint &outShader);
	bool IsCompiled(GLuint shader);
	bool IsValidProgram(); 

	void Bind(); 
	void Unload(); 


	void SetMatrixUniform(std::string name , const Matrix4& matrix); 
	void SetVectorUniform(std::string name, const Vector3 vector) ;
	void SetFloatUniform(std::string name, const GLfloat val); 


private:
	GLuint mShaderProgram; 
	GLuint mVertexShader; 
	GLuint mFragmentShader; 

	class Renderer* mRenderer; 
};

