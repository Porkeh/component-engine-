#version 430

uniform sampler2D tex;
uniform int test;
uniform int test2;
in vec2 texCoord;

out vec4 FragColour;

void main() {
	
	//FragColour = vec4(j,0,0,1);
   FragColour = texture(tex,texCoord);
}
