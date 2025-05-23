#version 410 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec2 in_Texcoords;
layout (location = 2) in vec3 in_Normal;

out vec3 FragPos;
out vec3 v_Normal;
out vec2 v_TexCoords;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	FragPos = (vec4(in_Position, 1.0) * u_Model).xyz;
	v_Normal = mat3(inverse(u_Model)) * in_Normal;
	v_TexCoords = in_Texcoords;

	gl_Position = vec4(FragPos, 1.) * u_View * u_Proj;
}