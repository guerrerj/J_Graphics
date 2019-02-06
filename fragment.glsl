#version 330 core

in vec2 UV;
in vec3 Normal_cameraspace;
in vec3 LightDirection_cameraspace;
in float LightPower;
in float dist;
in float LightColor;
in vec3 EyeDirection_cameraspace;

out vec3 color;

uniform sampler2D myTextureSampler;

void main()
{
    vec3 MaterialDiffuseColor = vec3(texture(myTextureSampler, UV).rgb);
    vec3 MaterialSpecularColor = vec3(0.9, 0.9, 0.9);

    vec3 n = normalize(Normal_cameraspace);

    vec3 l = normalize(LightDirection_cameraspace);

    vec3 MaterialAmbientColor = vec3(0.3, 0.3, 0.3) * MaterialDiffuseColor;

    vec3 E = normalize(EyeDirection_cameraspace);
    vec3 R = reflect(-l,n);
	float cosAlpha = clamp(dot(E,R),0,1);

	float cosTheta = clamp(dot(n,l),0,1);

	color = MaterialAmbientColor + 
	        MaterialDiffuseColor*LightColor*LightPower*cosTheta/(dist*dist)
	        + MaterialSpecularColor * LightColor*LightPower/2* pow(cosAlpha,8)/(dist*dist);

}

