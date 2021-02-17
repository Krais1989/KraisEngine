#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform float Time;
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

void main(){

	//gl_Position = MVP * vec4(aPos.xyz, 1.0);
	gl_Position = Projection * View * Model * vec4(aPos, 1.0);
	TexCoord = aTexCoord;
}
