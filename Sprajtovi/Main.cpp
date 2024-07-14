#include "Aplikacija.h"
#include <iostream>

int main()
{
	Aplikacija aplikacija(800, 600, 100, 60);

	aplikacija.Pokreni(pexel::AplikacijaApstrakt::VSync::FPS_60);
}