#version 330 core

layout(location = 0) in vec3 in_Position;    // Position du sommet

uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Proj;

void main() {

    mat4 MATRIX_VIEW_PROJECTION = u_Model * u_View * u_Proj;
    gl_Position = vec4(in_Position, 1.0) * MATRIX_VIEW_PROJECTION;

}
