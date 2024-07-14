#version 460 core

in vec2 pozicija;
in vec2 tekstura;

out vec4 boja;

struct Svetlo2D
{
	float intenzitet;
	vec2 pozicija;
	vec3 boja;
};

uniform sampler2D samp;
uniform Svetlo2D svetlo;

void main()
{
	float razdaljinaOdSvetla = svetlo.intenzitet / distance(svetlo.pozicija + svetlo.intenzitet, pozicija);
	float svetloNaPlocici = clamp(razdaljinaOdSvetla, 0.05f, 1.0f);

	boja = texture(samp, tekstura) * vec4(vec3(svetloNaPlocici) * svetlo.boja, 1.0f);
}