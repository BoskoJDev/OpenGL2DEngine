#pragma once
#include "GLEW/glew.h"
#include <cstdint>

namespace pexel
{
	class BaferElemenata
	{
	public:
		BaferElemenata();
		~BaferElemenata();

		void Crtaj(int brojIndica, uint32_t tipIndica);
		void PodesiPodPodatke(void* podaci, int velicinaPodataka, int ofset);
		void PodesiAtributeTemena(int indeks, int velicina, uint32_t tip, int velicinaPodataka, const void* ofset);
		void PodesiPodatke(void* podaci, int velicinaPodataka, uint32_t tipIscrtavanja,
			void* indice, int velicinaIndica, uint32_t tipIscrtavanjaIndica);

	private:
		uint32_t VAO, VBO, EBO;
	};
}