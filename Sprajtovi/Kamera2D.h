#pragma once
#include "BaferElemenata.h"
#include "Sejder.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace pexel
{
	class Kamera2D
	{
	public:
		Kamera2D(float leviKlip, float desniKlip, float gornjiKlip, float donjiKlip);

		void SetPozicija(const glm::vec2& pozicija);
		void SetPozicija(float x, float y);
		void Rotacija(float rotacija);
		void Zumiranje(float zumiranje);

		const glm::mat4& Projekcija() const;
		const glm::mat4& Pogled() const;
		const glm::mat4& VPMatrica() const;

	private:
		glm::vec2 pozicija;
		float rotacija = 0.0f;
		float zumiranje = 1.0f;

		glm::mat4 projekcija;
		glm::mat4 pogled;
		glm::mat4 viewProjectionMatrica;

		void AzurirajMatricu();
	};
}