#version 460 core

out vec4 FragColor;

uniform vec4 EmissiveColor;

void main()
{
	FragColor = EmissiveColor;
}