#version 120

attribute vec3 aVertexPosition;
attribute vec2 aUV;

varying vec2 vUV;

uniform mat4 mvMatrix;

void main(void)
{
	gl_Position = mvMatrix * vec4(aVertexPosition, 1.0);
	vUV = aUV;
}
