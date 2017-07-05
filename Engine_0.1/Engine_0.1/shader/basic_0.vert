#version 430

layout (location=0) in vec3 VertexPosition;
layout (location=1) in vec2 fragTexCoord;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec2 texCoord;

void main()
{
	texCoord = fragTexCoord;

    gl_Position = P * V * M * vec4(VertexPosition,1);
}
