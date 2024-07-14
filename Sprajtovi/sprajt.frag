#version 460 core

in vec2 Pozicija;
in vec2 Tekstura;

out vec4 Boja;

struct Svetlo2D
{
	float intenzitet;
	vec2 pozicija;
	vec3 boja;
};

uniform sampler2D tex;
uniform vec3 bojaSprajta;
uniform Svetlo2D svetlo;

void main()
{
	float razdaljinaOdSvetla = svetlo.intenzitet / distance(svetlo.pozicija + svetlo.intenzitet, Pozicija);
	float intenzitetSvetlaNaSprajtu = clamp(razdaljinaOdSvetla, 0.05f, 1.0f);
	vec3 vektorSvetla = vec3(bojaSprajta) * vec3(intenzitetSvetlaNaSprajtu);

	Boja = texture(tex, Tekstura) * vec4(vektorSvetla * svetlo.boja, 1.0f);
}