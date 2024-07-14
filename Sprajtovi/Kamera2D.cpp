#include "Kamera2D.h"

namespace pexel
{
	Kamera2D::Kamera2D(float leviKlip, float desniKlip, float gornjiKlip, float donjiKlip)
		: projekcija(glm::ortho(leviKlip, desniKlip, gornjiKlip, donjiKlip)), pogled(1.0f)
	{
		this->viewProjectionMatrica = this->projekcija * this->pogled;
	}

	void Kamera2D::SetPozicija(const glm::vec2& pozicija)
	{
		this->pozicija = pozicija;
		AzurirajMatricu();
	}

	void Kamera2D::SetPozicija(float x, float y)
	{
		this->pozicija = { x, y };
		AzurirajMatricu();
	}

	void Kamera2D::Rotacija(float rotacija)
	{
		this->rotacija = rotacija;
		AzurirajMatricu();
	}

	void Kamera2D::Zumiranje(float zumiranje)
	{
		this->zumiranje = zumiranje;
		AzurirajMatricu();
	}

	const glm::mat4& Kamera2D::Projekcija() const { return this->projekcija; }

	const glm::mat4& Kamera2D::Pogled() const { return this->pogled; }

	const glm::mat4& Kamera2D::VPMatrica() const { return this->viewProjectionMatrica; }

	void Kamera2D::AzurirajMatricu()
	{
		glm::mat4 transformacija =
			glm::translate(glm::mat4(1.0f), glm::vec3(this->pozicija, 0.0f)) *
			glm::rotate(glm::mat4(1.0f), glm::radians(this->rotacija), glm::vec3(0.0f, 0.0f, 1.0f));

		this->pogled = glm::inverse(transformacija);
		this->viewProjectionMatrica = this->projekcija * this->pogled;
	}
}