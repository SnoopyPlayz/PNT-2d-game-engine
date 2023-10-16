#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

uniform vec3 pos;
out vec2 TexCoord;

void main(){
	gl_Position = vec4(aPos[0] + pos[0], aPos[1] + pos[1], pos[2],1);
	TexCoord = aTexCoord;
};
