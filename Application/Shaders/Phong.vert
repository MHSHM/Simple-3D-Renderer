#version 330


uniform mat4 mWorldTransform ; 
uniform mat4 mViewProjection ; 

layout (location = 0) in vec3 inPos ; 
layout (location = 1) in vec3 inNormal ;
layout (location = 2) in vec2 texCoord ; 


out vec3 mFragPos ; 
out vec3 mNormal ; 

void main()
{
	vec4 pos = vec4(inPos , 1.0) ; 
	pos = pos * mWorldTransform ; 
	mFragPos = pos.xyz ; 
	gl_Position = pos * mViewProjection ; 

	mNormal = (vec4(inNormal, 0.0f) * mWorldTransform).xyz;
}