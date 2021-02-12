#version 460 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor;

uniform float Time;

uniform mat4 MVP;

void main(){

	//gl_Position = MVP * vec4(aPos.xyz, 1.0);
	gl_Position = vec4(aPos.xyz, 1.0);

	vertexColor = vec4(aPos.xyz, 1.0);
}
