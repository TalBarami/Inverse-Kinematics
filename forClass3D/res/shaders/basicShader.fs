#version 130

varying vec2 texCoord0;
varying vec3 normal0;
varying vec3 color0;

uniform vec3 lightDirection;
uniform vec3 pickColor;
uniform vec4 selected;
uniform sampler2D texture;

void main()
{
	if(texCoord0.x < 0.1f || texCoord0.x > 0.9f ||
		texCoord0.y < 0.1f || texCoord0.y > 0.9f){
		gl_FragColor =  vec4(0.0f, 0.0f, 0.0f, 1.0);
	} else {
		gl_FragColor = texture2D(texture,texCoord0) * selected;
	}
}
