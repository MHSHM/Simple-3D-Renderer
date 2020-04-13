#include "pch.h"
#include "Shader.h"
#include <fstream>
#include <sstream>
#include "Renderer.h"

Shader::Shader(Renderer* renderer) :
	mRenderer(renderer),
	mShaderProgram(0),
	mVertexShader(0),
	mFragmentShader(0)
{
	renderer->GetShaders().emplace_back(this); 
}

bool Shader::Load(std::string vertPath, std::string FragPath) 
{
	if (!Compile(vertPath , GL_VERTEX_SHADER , mVertexShader) 
	|| !Compile(FragPath, GL_FRAGMENT_SHADER, mFragmentShader)) 
	{
		return false;
	}

	mShaderProgram = glCreateProgram();
	glAttachShader(mShaderProgram, mVertexShader); 
	glAttachShader(mShaderProgram, mFragmentShader); 
	glLinkProgram(mShaderProgram); 

	if (!IsValidProgram()) 
	{
		return false; 
	}

	return true; 
}

void Shader::SetMatrixUniform(std::string name, const Matrix4& matrix)
{
	GLuint uniform = glGetUniformLocation(mShaderProgram , name.c_str());
	glUniformMatrix4fv(uniform , 1 , GL_TRUE , matrix.GetAsFloatPtr()); 
}

void Shader::SetVectorUniform(std::string name , const Vector3 vector) 
{
	GLuint uniform = glGetUniformLocation(mShaderProgram, name.c_str());
	glUniform3f(uniform, vector.x, vector.y, vector.z); 
}


void Shader::SetFloatUniform(std::string name , const GLfloat val) 
{
	GLuint uniform = glGetUniformLocation(mShaderProgram, name.c_str()); 
	glUniform1fv(uniform , 1 , &val); 
}

void Shader::Bind() 
{
	glUseProgram(mShaderProgram); 
}

void Shader::Unload() 
{
	glDeleteProgram(mShaderProgram); 
	glDeleteShader(mVertexShader); 
	glDeleteShader(mFragmentShader);
}

bool Shader::Compile(std::string path, GLenum type , GLuint &outShader)
{
	std::ifstream shader(path); 
	if (shader.is_open()) 
	{
		std::stringstream sstream; 
		sstream << shader.rdbuf(); 
		std::string content = sstream.str();
		const char* contentStr = content.c_str(); 

		outShader = glCreateShader(type); 
		glShaderSource(outShader, 1, &(contentStr), nullptr); 
		glCompileShader(outShader); 

		if (!IsCompiled(outShader)) 
		{
			SDL_Log("Failed to compile shader %s", path.c_str());
			return false;
		}
	}
	else 
	{
		SDL_Log("Failed to open shader file %s", path.c_str());
		return false;
	}
	return true; 
}


bool Shader::IsCompiled(GLuint shader)
{
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetShaderInfoLog(shader, 511, nullptr, buffer);
		SDL_Log("GLSL Compile Failed:\n%s", buffer);
		return false;
	}

	return true;
}

bool Shader::IsValidProgram()
{

	GLint status;
	// Query the link status
	glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &status);
	if (status != GL_TRUE)
	{
		char buffer[512];
		memset(buffer, 0, 512);
		glGetProgramInfoLog(mShaderProgram, 511, nullptr, buffer);
		SDL_Log("GLSL Link Status:\n%s", buffer);
		return false;
	}

	return true;
}

Shader::~Shader()
{
}
