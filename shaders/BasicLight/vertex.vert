#version 410 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;

out vec3 FragPos;
out vec3 v_Normal;

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main()
{
	mat4 MATRIX_VIEW_PROJECTION = u_Model * u_View * u_Proj;

	gl_Position = vec4(in_Position, 1) * MATRIX_VIEW_PROJECTION;
	FragPos = vec3(u_Model * vec4(in_Position, 1.0));

	v_Normal = in_Normal;
}