#version 430

// coming from the mesh properties
in vec4 in_Position;

// coming from the setUniforms in the helloworld.hpp file
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main(void)
{	
	vec4 transformed_vertex = projectionMatrix * viewMatrix * modelMatrix * in_Position;

	 gl_Position = transformed_vertex;
}