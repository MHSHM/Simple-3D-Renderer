#version 330 


uniform vec3 mLightSource ; 
uniform vec3 mLightColor ; 
uniform vec3 mViewPosition ; 
uniform float mAmbientStrength ; 
uniform float mSpecularPower ; 

in vec3 mFragPos ; 
in vec3 mNormal ; 


out vec4 FragColor ;

void main()
{
	// Calculating ambient light 
	vec3 ambient =  mAmbientStrength * mLightColor ;  

	// Calculating Diffuse Light
	vec3 norm = normalize(mNormal) ;
	vec3 lightDir = normalize(mLightSource - mFragPos) ; 
	float diff = max(dot(norm , lightDir) , 0.0) ; 
	vec3 diffuse = diff * mLightColor ; 

	// Calculating Specular light
	vec3 viewDir = normalize(mViewPosition - mFragPos) ; 
	vec3 reflectDir = reflect(-lightDir , norm) ; 
	float spec = pow(max(dot(viewDir , reflectDir) , 0.0) , mSpecularPower) ; 
	vec3 specular = spec * mLightColor ; 

	vec3 final = (ambient + diffuse + specular) * vec3(0.5, 0.5, 0.3) ; 
    FragColor = vec4(final, 1.0);
} 