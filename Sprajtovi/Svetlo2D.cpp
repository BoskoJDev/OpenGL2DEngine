#include "Svetlo2D.h"

namespace pexel
{
	Objekat<Tekstura2D> Svetlo2D::teksturaSvetla = nullptr;
	Objekat<Sejder> Svetlo2D::sejderSvetla = nullptr;

	Svetlo2D::Svetlo2D(const glm::vec2& _pozicija, float _intenzitet, const glm::vec3& _boja)
		: pozicija(_pozicija), intenzitet(_intenzitet), boja(_boja)
	{
		if (!ObjekatValidan(teksturaSvetla) && !ObjekatValidan(sejderSvetla))
		{
			teksturaSvetla = KreirajObjekat<Tekstura2D>("svetlo.png", true);
			sejderSvetla = KreirajObjekat<Sejder>("svetlo.vert", "svetlo.frag");
		}
		this->baferSvetla = KreirajObjekat<BaferElemenata>();

		uint32_t indice[6] = {
			0, 1, 2,
			2, 3, 0
		};

		this->baferSvetla->PodesiPodatke(nullptr, 16 * sizeof(float), GL_STATIC_DRAW, indice, sizeof(indice), GL_STATIC_DRAW);
		this->baferSvetla->PodesiAtributeTemena(0, 2, GL_FLOAT, 4 * sizeof(float), nullptr);
		this->baferSvetla->PodesiAtributeTemena(1, 2, GL_FLOAT, 4 * sizeof(float), (const void*)(2 * sizeof(float)));
	}

	std::tuple<float, glm::vec2, glm::vec3> Svetlo2D::SvojstvaSvetla() const
	{
		return std::make_tuple(this->intenzitet, this->pozicija, this->boja);
	}

	void Svetlo2D::Crtaj(const glm::mat4& matricaKamere)
	{
		teksturaSvetla->Povezi(1);

		sejderSvetla->Koristi();
		{
			sejderSvetla->SetInt("sempl", 1);
			sejderSvetla->SetVec3("boja", this->boja);
			sejderSvetla->SetMat4("projekcija", matricaKamere);

			//'Intenzitet' ce pretstavljati poluprecnik kada se tekstura svetla bude iscrtavala
			float precnik = this->intenzitet * 2;

			float temena[16] = {
				this->pozicija.x, this->pozicija.y, 0.0f, 0.0f,
				this->pozicija.x + precnik, this->pozicija.y, 1.0f, 0.0f,
				this->pozicija.x + precnik, this->pozicija.y + precnik, 1.0f, 1.0f,
				this->pozicija.x, this->pozicija.y + precnik, 0.0f, 1.0f
			};

			this->baferSvetla->PodesiPodPodatke(temena, sizeof(temena), 0);
			this->baferSvetla->Crtaj(6, GL_UNSIGNED_INT);
		}
		sejderSvetla->NeKoristi();

		teksturaSvetla->NePovezi();
	}
}