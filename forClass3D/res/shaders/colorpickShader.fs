#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 pickColor;

void main()
{
	gl_FragColor =  vec4(pickColor.x, pickColor.y, pickColor.z, 1.0f);
}
