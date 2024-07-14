#pragma once
#include "GLEW/glew.h"
#include <cstdint>
#include <iostream>

namespace pexel
{
	class Tekstura2D
	{
	public:
		Tekstura2D(const char* fajl, bool flipVertikalno);
		~Tekstura2D();

		const int Sirina() const;
		const int Visina() const;

		void Povezi(uint32_t slot = 0) const;
		void NePovezi() const;

	private:
		int sirina, visina;
		uint32_t tekstura;
	};
}