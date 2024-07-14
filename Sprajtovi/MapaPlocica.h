#pragma once
#include <iostream>
#include "GLEW/glew.h"
#include "Sejder.h"
#include "Tekstura2D.h"
#include "Svetlo2D.h"
#include "BaferElemenata.h"
#include "Objekat.h"

namespace pexel
{
	class MapaPlocica
	{
	public:
		MapaPlocica(const char* fajl, const char* mapaPlocica, int velicinaPlocice, float velicina);

		void CrtajPlocice(const glm::mat4& matricaKamere, const Objekat<Svetlo2D>& svetlo = nullptr);
		void PrikaziBrojXYIndeksa();

	private:
		BaferElemenata bafer;
		Objekat<Tekstura2D> tekstura;

		int velicinaPlocice;
		int sirinaAtlasa, visinaAtlasa;

		int brojIndica = 0;

		float velicina;

		std::ifstream fajlPlocica;

		static Objekat<Sejder> sejder;

		std::vector<glm::ivec2> indeksiPlocica;

		void PostavkaBafera();

		struct Cetvorougao
		{
			glm::vec4 t1, t2, t3, t4;

			static Cetvorougao KreirajCetvorougao(MapaPlocica* mapa, glm::vec2& pozicija, glm::vec2& texKoord);
		};
	};
}