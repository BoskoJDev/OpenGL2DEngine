#pragma once
#include <deque>
#include <array>
#include "GLEW/glew.h"
#include "Sejder.h"
#include "Tekstura2D.h"
#include "BaferElemenata.h"
#include "Svetlo2D.h"
#include "Objekat.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace pexel
{
	class Sprajt
	{
	public:
		Sprajt(const char* sprajt, const glm::vec2& pozicija, const glm::vec2& velicina, bool flipVertikalno = true);

		void PostavkaAnimacija(int brojAnimacija, int xfrejmovi, int yfrejmovi);
		void PocetniKrajnjiFrejmovi(int indeks, int pocetniXFrejm, int pocetniYFrejm, int krajnjiXFrejm, int krajnjiYFrejm);
		void SetBrzinaAnimacije(int indeks, float brzinaAnimacije);
		void SetIndeksAnimacije(int _indeks);

		void SetPozicija(const glm::vec2& _pozicija);
		void SetPozicija(float x, float y);
		void SetVelicina(const glm::vec2& _velicina);
		void SetVelicina(float w, float h);

		const glm::vec2& Pozicija() const;
		const glm::vec2& Velicina() const;

		void Azuriraj(const glm::mat4& matricaKamere, float deltaVreme, const Objekat<Svetlo2D>& svetlo = nullptr,
			float rotacija = 0.0f, const glm::vec3& bojaSprajta = glm::vec3(1.0f));

	private:
		BaferElemenata bafer;
		Objekat<Tekstura2D> tekstura;
		float sirina, visina;

		int indeksAnimacije = 0;

		glm::vec2 pozicija;
		glm::vec2 velicina;

		static int slot;

		static Objekat<Sejder> sejder;

		class Animacija
		{
		public:
			Animacija(int _xfrejmovi, int _yfrejmovi);

			void SetBrzinaAnimacije(float brzinaAnimacije);
			void SetPocetneFrejmove(int _pocetniXFrejm, int _pocetniYFrejm);
			void SetKrajnjeFrejmove(int _krajnjiXFrejm, int _krajnjiYFrejm);
			std::array<glm::vec4, 4>& AzuriranaTemena(Sprajt* sprajt, float deltaVreme);

			bool JeZavrsena() const;

		private:
			int xfrejmovi;
			int yfrejmovi;

			float brzinaAnimacije;

			float trenutniXFrejm;
			float trenutniYFrejm;
			int pocetniXFrejm;
			int pocetniYFrejm;
			int krajnjiXFrejm;
			int krajnjiYFrejm;
		};

		std::deque<Animacija> animacije;
	};
}