#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 vertexNormal_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 ShadowCoord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 DepthBiasMVP;


void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	
	ShadowCoord = DepthBiasMVP * vec4(vertexPosition_modelspace,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}

