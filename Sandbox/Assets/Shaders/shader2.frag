#version 460 core

out vec4 FragColor;

in vec4 vertexColor;

uniform float Time;

void main()
{
	//FragColor = vec4(1.0f, .9f, 0.2f, 1.0f);
	float p = sin(Time) / 2f + .5f;
	FragColor = vec4(1.0f, .9f, 0.2f, 1.0f) * p + vertexColor * (1f-p);
}