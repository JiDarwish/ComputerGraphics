#version 430

// coming from the mesh properties
in vec4 in_Position;

// coming from the setUniforms in the shading.hpp file
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main(void)
{	

	vec4 vert = in_Position;

	// transform position and project
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vert;
}