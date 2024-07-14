#pragma once
#include "PexelPogon.h"

class Aplikacija : public pexel::AplikacijaApstrakt
{
public:
	using pexel::AplikacijaApstrakt::AplikacijaApstrakt; // Nasledjivanje konstruktora

	virtual bool Postavke() override;
	virtual bool Azuriranje(float deltaVreme) override;
private:
	glm::vec2 pozicijaIgraca = glm::vec2(50.0f, 100.0f);

	pexel::Unos* unos;

	pexel::Objekat<pexel::Sprajt> ratnica;
	pexel::Objekat<pexel::Sprajt> ratnica2;
	pexel::Objekat<pexel::Kamera2D> kamera;
	pexel::Objekat<pexel::MapaPlocica> mapa;
	pexel::Objekat<pexel::Svetlo2D> svetlo;

	void ProcesirajTastaturu(float deltaVreme);
};