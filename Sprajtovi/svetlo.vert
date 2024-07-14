#version 460 core

layout(location = 0) in vec2 pozicija;
layout(location = 1) in vec2 tekstura;

out vec2 Tekstura;

uniform mat4 projekcija;

void main()
{
	Tekstura = tekstura;
	gl_Position = projekcija * vec4(pozicija, 0.0f, 1.0f);
}