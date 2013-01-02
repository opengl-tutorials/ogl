#version 120

// Input vertex data, different for all executions of this shader.
attribute vec3 vertexPosition_modelspace;
attribute vec3 vertexColor;

// Output data ; will be interpolated for each fragment.
varying vec3 fragmentColor;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;

void main(){	

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);

	// The color of each vertex will be interpolated
	// to produce the color of each fragment
	fragmentColor = vertexColor;
}

