#version 460 core

in vec2 Tekstura;

out vec4 Boja;

uniform sampler2D sempl;
uniform vec3 boja;

void main()
{
	Boja = texture(sempl, Tekstura) * vec4(boja, 1.0f);
}