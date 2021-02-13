#version 460 core

in vec2 TexCoord;

uniform float Time;

uniform sampler2D texture1;
uniform sampler2D texture2;

out vec4 FragColor;

void main()
{
	float p = sin(Time) / 2f + .5f;
	
	//FragColor = texture2D(texture2, TexCoord);
	//FragColor = texture(texture1, TexCoord);
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), p);

	//FragColor.xyz = mix(vec3(1,0,0), vec3(0,0,1), p);
	FragColor.a = 1.0f;

}