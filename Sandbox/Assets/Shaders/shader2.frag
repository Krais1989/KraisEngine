#version 460 core

in vec2 TexCoord;

uniform float Time;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main()
{
	//float p = sin(Time) / 2f + .5f;
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), p);
	FragColor = texture(texture1, TexCoord);

}