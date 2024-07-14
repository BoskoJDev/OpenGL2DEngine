#include "Unos.h"

namespace pexel
{
	Unos::Taster Unos::tasteri[1024];
	int Unos::indeksZadnjegPritisnutogTastera = 0;

	Unos::Unos(AplikacijaApstrakt* aplikacija) { glfwSetKeyCallback(aplikacija->Prozor(), FunkcijaTastature);	}

	void Unos::FunkcijaTastature(GLFWwindow*, int taster, int, int akcija, int)
	{
		if (akcija == GLFW_PRESS || akcija == GLFW_REPEAT)
		{
			tasteri[taster].pritisnut = true;
			tasteri[taster].pusten = false;
			tasteri[taster].taster = TasterTastature(taster);
			indeksZadnjegPritisnutogTastera = taster;
		}
		if (akcija == GLFW_RELEASE)
		{
			tasteri[taster].pritisnut = false;
			tasteri[taster].pusten = true;
		}
	}

	Unos* Unos::GetInstanca(AplikacijaApstrakt* aplikacija)
	{
		static Unos instanca(aplikacija);
		return &instanca;
	}

	bool Unos::TasterPritisnut(TasterTastature taster) const { return tasteri[int(taster)].pritisnut; }

	bool Unos::TasterPusten(TasterTastature taster) const { return tasteri[int(taster)].pusten; }
	
	TasterTastature Unos::ZadnjiPritisnutTaster() const
	{
		return tasteri[indeksZadnjegPritisnutogTastera].taster;
	}
}