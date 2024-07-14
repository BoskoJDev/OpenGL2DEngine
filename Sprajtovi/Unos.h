#pragma once
#include "AplikacijaApstrakt.h"
#include "KodoviTasteraZaUlaz.h"

namespace pexel
{
	class Unos
	{
	public:
		static Unos* GetInstanca(AplikacijaApstrakt* aplikacija);

		bool TasterPritisnut(TasterTastature taster) const;
		bool TasterPusten(TasterTastature taster) const;

		TasterTastature ZadnjiPritisnutTaster() const;

	private:
		Unos(AplikacijaApstrakt* aplikacija);

		static void FunkcijaTastature(GLFWwindow*, int taster, int, int akcija, int);

		struct Taster
		{
			bool pritisnut;
			bool pusten;
			TasterTastature taster;
		};

		static Taster tasteri[1024];

		static int indeksZadnjegPritisnutogTastera;
	};
}