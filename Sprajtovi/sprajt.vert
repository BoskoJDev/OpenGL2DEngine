#version 460 core

layout(location = 0) in vec4 vektor; // x,y - pozicija; z,w - koordinate teksture

out vec2 Pozicija;
out vec2 Tekstura;

uniform mat4 mvp; // Skraceno za 'model-view-projection' matricu

void main()
{
	Pozicija = vektor.xy;
	Tekstura = vektor.zw;
	gl_Position = mvp * vec4(Pozicija, 0.0f, 1.0f);
}