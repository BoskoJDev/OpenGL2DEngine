#include "Sprajt.h"

namespace pexel
{
	int Sprajt::slot = 2; // Slotovi '0'(za mapu plocica) i '1'(za teksturu svetla) su zauzeti
	Objekat<Sejder> Sprajt::sejder = nullptr;

	Sprajt::Sprajt(const char* sprajt, const glm::vec2& _pozicija, const glm::vec2& _velicina, bool flipVertikalno)
		: pozicija(_pozicija), velicina(_velicina)
	{
		unsigned int indice[6] = {
			0, 1, 2,
			2, 3, 0
		};

		this->bafer.PodesiPodatke(nullptr, 4 * sizeof(glm::vec4), GL_STATIC_DRAW, indice, sizeof(indice), GL_STATIC_DRAW);
		this->bafer.PodesiAtributeTemena(0, 4, GL_FLOAT, 4 * sizeof(float), nullptr);

		this->tekstura = KreirajObjekat<Tekstura2D>(sprajt, flipVertikalno);
		sejder = KreirajObjekat<Sejder>("sprajt.vert", "sprajt.frag");

		this->sirina = float(this->tekstura->Sirina());
		this->visina = float(this->tekstura->Visina());

		//Zbog ogranicenja sto se tice slotova tekstura (32 je ogranicenje)
		if (slot == 31)
			slot = 2;
		else
			slot++;
	}

	void Sprajt::PostavkaAnimacija(int brojAnimacija, int xfrejmovi, int yfrejmovi)
	{
		for (int i = 0; i < brojAnimacija; i++)
			this->animacije.emplace_back(xfrejmovi, yfrejmovi);
	}

	void Sprajt::PocetniKrajnjiFrejmovi(int indeks, int pocetniXFrejm, int pocetniYFrejm, int krajnjiXFrejm, int krajnjiYFrejm)
	{
		this->animacije[indeks].SetPocetneFrejmove(pocetniXFrejm, pocetniYFrejm);
		this->animacije[indeks].SetKrajnjeFrejmove(krajnjiXFrejm, krajnjiYFrejm);
	}

	void Sprajt::SetBrzinaAnimacije(int indeks, float brzinaAnimacije)
	{
		if (indeks > this->animacije.size() - 1)
		{
			std::cerr << "Postavljeni indeks je veci od kolicine postavljenih animacija!\n";
			return;
		}

		this->animacije[indeks].SetBrzinaAnimacije(brzinaAnimacije);
	}

	void Sprajt::SetIndeksAnimacije(int _indeks)
	{
		if (_indeks > this->animacije.size() - 1)
		{
			std::cerr << "Animacija sa indeksom " << _indeks << " ne postoji!\n";
			return;
		}

		this->indeksAnimacije = _indeks;
	}

	void Sprajt::SetPozicija(const glm::vec2& _pozicija) { this->pozicija = _pozicija; }

	void Sprajt::SetPozicija(float x, float y) { this->pozicija = { x, y }; }

	void Sprajt::SetVelicina(const glm::vec2& _velicina) { this->velicina = _velicina; }

	void Sprajt::SetVelicina(float w, float h) { this->velicina = { w, h }; }

	const glm::vec2& Sprajt::Pozicija() const { return this->pozicija; }

	const glm::vec2& Sprajt::Velicina() const { return this->velicina; }

	void Sprajt::Azuriraj(const glm::mat4& matricaKamere, float deltaVreme, const Objekat<Svetlo2D>& svetlo, float rotacija, const glm::vec3& bojaSprajta)
	{
		Animacija* animacija{};

		if (this->animacije.size() > 0)
			animacija = &this->animacije[this->indeksAnimacije];

		sejder->Koristi();
		{
			this->tekstura->Povezi(slot + 1);
			sejder->SetInt("tex", slot + 1);

			glm::mat4 model(1.0f);

			// Da bi se sprajt rotirao oko svoje ose
			model = glm::translate(model, glm::vec3(this->pozicija + (0.5f * this->velicina), 0.0f));
			model = glm::rotate(model, glm::radians(rotacija), glm::vec3(0.0f, 0.0f, 1.0f));
			model = glm::translate(model, glm::vec3(-(this->pozicija + (0.5f * this->velicina)), 0.0f));

			glm::mat4 mvp = matricaKamere * model;

			sejder->SetMat4("mvp", mvp);
			sejder->SetVec3("bojaSprajta", bojaSprajta);
			
			// Objekat ne mora biti osvetljen
			if (ObjekatValidan((Objekat<Svetlo2D>&)svetlo))
			{
				auto&&[intenzitetSvetla, pozicijaSvetla, bojaSvetla] = svetlo->SvojstvaSvetla();
				sejder->SetFloat("svetlo.intenzitet", intenzitetSvetla);
				sejder->SetVec2("svetlo.pozicija", pozicijaSvetla);
				sejder->SetVec3("svetlo.boja", bojaSvetla);
			}

			std::array<glm::vec4, 4> temena;

			if (!animacija)
			{
				temena = {
					glm::vec4(this->pozicija, 0.0f, 0.0f),
					glm::vec4(this->pozicija.x + this->velicina.x, this->pozicija.y, 1.0f, 0.0f),
					glm::vec4(this->pozicija + this->velicina, 1.0f, 1.0f),
					glm::vec4(this->pozicija.x, this->pozicija.y + this->velicina.y, 0.0f, 1.0f)
				};

				(void)deltaVreme;
			}
			else
			{
				temena = animacija->AzuriranaTemena(this, deltaVreme);
			}

			this->bafer.PodesiPodPodatke(temena.data(), sizeof(glm::vec4) * temena.size(), 0);

			this->bafer.Crtaj(6, GL_UNSIGNED_INT);
			this->tekstura->NePovezi();
		}
		sejder->NeKoristi();
	}

	Sprajt::Animacija::Animacija(int _xfrejmovi, int _yfrejmovi) : xfrejmovi(_xfrejmovi), yfrejmovi(_yfrejmovi)
	{
		this->brzinaAnimacije = 0.0f;
	}

	void Sprajt::Animacija::SetBrzinaAnimacije(float brzinaAnimacije)
	{
		this->brzinaAnimacije = brzinaAnimacije;
	}

	void Sprajt::Animacija::SetPocetneFrejmove(int _pocetniXFrejm, int _pocetniYFrejm)
	{
		this->pocetniXFrejm = _pocetniXFrejm;
		this->pocetniYFrejm = _pocetniYFrejm;

		this->trenutniXFrejm = float(this->pocetniXFrejm);
		this->trenutniYFrejm = float(this->pocetniYFrejm);
	}

	void Sprajt::Animacija::SetKrajnjeFrejmove(int _krajnjiXFrejm, int _krajnjiYFrejm)
	{
		this->krajnjiXFrejm = _krajnjiXFrejm;
		this->krajnjiYFrejm = _krajnjiYFrejm;
	}

	std::array<glm::vec4, 4>& Sprajt::Animacija::AzuriranaTemena(Sprajt* s, float deltaVreme)
	{
		if (int(this->trenutniXFrejm) == this->krajnjiXFrejm)
		{
			this->trenutniXFrejm = float(this->pocetniXFrejm);
			this->trenutniYFrejm++;
		}

		if (int(this->trenutniYFrejm) == this->krajnjiYFrejm)
			this->trenutniYFrejm = float(this->pocetniYFrejm);

		const float sirinaSprajta = s->sirina / this->xfrejmovi + 2;
		const float visinaSprajta = s->visina / this->yfrejmovi;

		float trenutniXFrejmZaokruzen = floorf(this->trenutniXFrejm);

		std::array<glm::vec4, 4> temena = {
			glm::vec4(s->pozicija, (trenutniXFrejmZaokruzen * sirinaSprajta) / s->sirina, (this->trenutniYFrejm * visinaSprajta) / s->visina),
			glm::vec4(s->pozicija.x + s->velicina.x, s->pozicija.y, ((trenutniXFrejmZaokruzen + 1) * sirinaSprajta) / s->sirina, (this->trenutniYFrejm * visinaSprajta) / s->visina),
			glm::vec4(s->pozicija + s->velicina, ((trenutniXFrejmZaokruzen + 1) * sirinaSprajta) / s->sirina, ((this->trenutniYFrejm + 1) * visinaSprajta) / s->visina),
			glm::vec4(s->pozicija.x, s->pozicija.y + s->velicina.y, (trenutniXFrejmZaokruzen * sirinaSprajta) / s->sirina, ((this->trenutniYFrejm + 1) * visinaSprajta) / s->visina),
		};

		this->trenutniXFrejm += this->brzinaAnimacije * deltaVreme;

		return temena;
	}

	bool Sprajt::Animacija::JeZavrsena() const
	{
		return this->trenutniXFrejm == this->krajnjiXFrejm && this->trenutniYFrejm == this->krajnjiYFrejm;
	}
}