#version 460 core

in vec2 TexCoord;

uniform sampler2D Texture_1;
uniform vec4 AmbientColor;

out vec4 FragColor;

void main()
{
	//float p = sin(Time) / 2f + .5f;
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), p);

	FragColor = texture(Texture_1, TexCoord) * AmbientColor;

	//FragColor = vec4(1,.6,.3,1);
}