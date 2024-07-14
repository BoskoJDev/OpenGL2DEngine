#version 460 core

layout(location = 0) in vec4 pos_tex;

out vec2 pozicija;
out vec2 tekstura;

uniform mat4 mvp;

void main()
{
	pozicija = pos_tex.xy;
	tekstura = pos_tex.zw;
	gl_Position = mvp * vec4(pozicija, 0.0f, 1.0f);
}