#version 410 core

layout(location=0) in vec3 a_Position;
out vec4 v_Color;

uniform mat4 u_MVP;

void main()
{
  gl_Position = u_MVP*vec4(a_Position, 1.0);
  v_Color = abs(gl_Position);
};
