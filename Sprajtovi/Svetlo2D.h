#pragma once
#include "GLEW/glew.h"
#include "glm/glm.hpp"
#include "Tekstura2D.h"
#include "BaferElemenata.h"
#include "Sejder.h"
#include "Objekat.h"
#include <tuple>

namespace pexel
{
	class Svetlo2D
	{
	public:
		Svetlo2D(const glm::vec2& _pozicija, float _intenzitet, const glm::vec3& _boja = glm::vec3(1.0f));

		std::tuple<float, glm::vec2, glm::vec3> SvojstvaSvetla() const;

		void Crtaj(const glm::mat4& matrica);

	private:
		float intenzitet;
		glm::vec2 pozicija;
		glm::vec3 boja;

		Objekat<BaferElemenata> baferSvetla;

		static Objekat<Tekstura2D> teksturaSvetla;
		static Objekat<Sejder> sejderSvetla;
	};
}