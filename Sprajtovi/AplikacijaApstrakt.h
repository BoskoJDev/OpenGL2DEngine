#pragma once
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "box2d/box2d.h"
#include <string>
#include <iostream>

namespace pexel
{
	class AplikacijaApstrakt
	{
	public:
		AplikacijaApstrakt();

		AplikacijaApstrakt(int sirinaProzora, int visinaProzora, int xPozicija = 50, int yPozicija = 50);

		GLFWwindow* Prozor() const;

		// MORAJU BITI PREKLOPLJENE DA BI APLIKACIJA RADILA!
		virtual bool Postavke() = 0;
		virtual bool Azuriranje(float deltaVreme) = 0;

		/* Moze biti preklopljena ukoliko korisnik mora dealocirati memoriju, zatvoriti fajlove itd, ali ne mora se
		preklopiti ukoliko nije potrebno*/
		virtual bool OslobadjanjeResursa() { return true; }

		enum class VSync : char
		{
			ISKLUCENO,
			FPS_60,
			FPS_30
		};

		void Pokreni(VSync fpsOgranicenje);

	protected:
		GLFWwindow* prozor;
		int sirinaProzora, visinaProzora;

	private:
		void Terminiraj(const char* poruka = nullptr);
		static void DebugFunkcija(uint32_t izvor, uint32_t tip, uint32_t id, uint32_t ozbiljnost, int duzina, const char* poruka, const void*);
	};
}