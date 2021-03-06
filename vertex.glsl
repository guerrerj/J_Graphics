#version 330 core
layout(location = 0) in vec3 vertexPosition_modelspace;

layout(location = 1) in vec2 vertexUV;

layout(location = 2) in vec3 vertexNormal_modelspace;

uniform mat4 MVP, M, V;
uniform float D, LP, LC;

out vec2 UV;
out float dist;
out float LightPower;
out float LightColor;
out vec3 LightDirection_cameraspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;

void main()
{
    vec3 LightPosition_worldspace = vec3(3, 1, 4);
	
	gl_Position = MVP * vec4(vertexPosition_modelspace,1);

	

	vec3 Position_worldspace = (M*vec4(vertexPosition_modelspace,1)).xyz;
	
	
	vec3 vertexPosition_cameraspace = (V*M*vec4(vertexPosition_modelspace,1)).xyz;
    EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace;
	
	
	
	vec3 LightPosition_cameraspace = (V*vec4(LightPosition_worldspace,1)).xyz;
    LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	
	Normal_cameraspace = (V*M*vec4(vertexNormal_modelspace,0)).xyz; 
	
	UV = vertexUV;
	dist = D;
	LightPower = LP;
	LightColor = LC;
}
