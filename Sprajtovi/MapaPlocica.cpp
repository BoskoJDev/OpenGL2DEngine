#include "MapaPlocica.h"

namespace pexel
{
	Objekat<Sejder> MapaPlocica::sejder = nullptr;

	static constexpr glm::ivec2 VEKTOR_ZA_ODBITI(INT_MIN);
	static constexpr glm::ivec2 VEKTOR_ZA_PRESKAKANJE(-1);

	MapaPlocica::MapaPlocica(const char* fajl, const char* mapaPlocica, int velicinaPlocice, float velicina)
		: velicinaPlocice(velicinaPlocice), velicina(velicina)
	{
		this->tekstura = KreirajObjekat<Tekstura2D>(fajl, true);
		sejder = KreirajObjekat<Sejder>("plocice.vert", "plocice.frag");

		this->sirinaAtlasa = this->tekstura->Sirina();
		this->visinaAtlasa = this->tekstura->Visina();

		this->fajlPlocica.open(mapaPlocica);
		if (int y = 0; this->fajlPlocica.is_open())
		{
			std::string s;
			while (std::getline(this->fajlPlocica, s, ','))
			{
				bool uslov = s._Equal("y");

				glm::ivec2 vektor = !uslov ? glm::ivec2(std::stoi(s), y) : VEKTOR_ZA_ODBITI;
				this->indeksiPlocica.push_back(vektor);

				y += uslov; // promenljiva ce se povecati za jedan samo ako uslov vrati jedinicu
			}
		}
		else
		{
			std::cout << "Fajl " << mapaPlocica << " nije pronadjen!\n";
		}

		PostavkaBafera();
	}

	void MapaPlocica::CrtajPlocice(const glm::mat4& matricaKamere, const Objekat<Svetlo2D>& svetlo)
	{
		this->tekstura->Povezi();

		sejder->Koristi();
		{
			sejder->SetInt("samp", 0);
			sejder->SetMat4("mvp", matricaKamere);

			// Objekat ne mora biti osvetljen
			if (ObjekatValidan((Objekat<Svetlo2D>&)svetlo))
			{
				auto&&[intenzitetSvetla, pozicijaSvetla, bojaSvetla] = svetlo->SvojstvaSvetla();
				sejder->SetFloat("svetlo.intenzitet", intenzitetSvetla);
				sejder->SetVec2("svetlo.pozicija", pozicijaSvetla);
				sejder->SetVec3("svetlo.boja", bojaSvetla);
			}
			
			this->bafer.Crtaj(brojIndica, GL_UNSIGNED_INT);
		}
		sejder->NeKoristi();

		this->tekstura->NePovezi();
	}

	void MapaPlocica::PrikaziBrojXYIndeksa()
	{
		const int X_INDEKSI = this->tekstura->Sirina() / this->velicinaPlocice;
		const int Y_INDEKSI = this->tekstura->Visina() / this->velicinaPlocice;

		std::cout << "Broj X plocica: " << X_INDEKSI << '\n' << "Broj Y plocica: " << Y_INDEKSI
			<< '\n' << "Ukupan broj plocica : " << X_INDEKSI * Y_INDEKSI << '\n';
	}

	void MapaPlocica::PostavkaBafera()
	{
		const int X_INDEKSI = this->tekstura->Sirina() / this->velicinaPlocice;

		std::vector<Cetvorougao> temena;
		for (int _x = 0; const auto& vektor : this->indeksiPlocica)
		{
			/* Ako je trenutni vektor jednak 'nevazecem' vektoru, horizontalni ofset se vraca na nulu, prelazi se na
			sledeci red i ne pravi se novi cetvorougao*/
			if (vektor == VEKTOR_ZA_ODBITI)
			{
				_x = 0;
				continue;
			}

			//Ako je trenutni vektor jednak vektoru 'za preskakanje', plocica se nece crtati na njegovoj poziciji
			if (vektor == VEKTOR_ZA_PRESKAKANJE) { continue; }

			int xIndeks = vektor.x % X_INDEKSI;
			int yIndeks = vektor.x / X_INDEKSI;

			glm::vec2 pozicija = { _x, vektor.y };
			glm::vec2 koordinateTeksture = { xIndeks , yIndeks };

			temena.push_back(Cetvorougao::KreirajCetvorougao(this, pozicija, koordinateTeksture));
			this->brojIndica += 6;
			_x++;
		}

		uint32_t* indice = new uint32_t[this->brojIndica];
		int ofset = 0;

		for (int i = 0; i < this->brojIndica; i += 6)
		{
			indice[i + 0] = 0 + ofset;
			indice[i + 1] = 1 + ofset;
			indice[i + 2] = 2 + ofset;
			indice[i + 3] = 2 + ofset;
			indice[i + 4] = 3 + ofset;
			indice[i + 5] = 0 + ofset;

			ofset += 4;
		}

		bafer.PodesiPodatke(temena.data(), sizeof(Cetvorougao) * temena.size(), GL_STATIC_DRAW,
			indice, brojIndica * sizeof(indice), GL_STATIC_DRAW);
		this->bafer.PodesiAtributeTemena(0, 4, GL_FLOAT, sizeof(glm::vec4), nullptr);

		delete[] indice;
		this->indeksiPlocica.clear();
	}

	MapaPlocica::Cetvorougao MapaPlocica::Cetvorougao::KreirajCetvorougao(MapaPlocica* mapa, glm::vec2& pozicija,
		glm::vec2& texKoord)
	{
		glm::vec2 teksturalneKoordinate[4] = {
			{ (texKoord.x * mapa->velicinaPlocice) / mapa->sirinaAtlasa, (texKoord.y * mapa->velicinaPlocice) / mapa->visinaAtlasa },
			{ ((texKoord.x + 1) * mapa->velicinaPlocice) / mapa->sirinaAtlasa, (texKoord.y * mapa->velicinaPlocice) / mapa->visinaAtlasa },
			{ ((texKoord.x + 1) * mapa->velicinaPlocice) / mapa->sirinaAtlasa, ((texKoord.y + 1) * mapa->velicinaPlocice) / mapa->visinaAtlasa },
			{ (texKoord.x * mapa->velicinaPlocice) / mapa->sirinaAtlasa, ((texKoord.y + 1) * mapa->velicinaPlocice) / mapa->visinaAtlasa }
		};

		glm::vec4 t1 = { pozicija * mapa->velicina, teksturalneKoordinate[0] };
		glm::vec4 t2 = { 
			mapa->velicina + (pozicija.x * mapa->velicina), pozicija.y * mapa->velicina, teksturalneKoordinate[1]
		};
		glm::vec4 t3 = {
			(pozicija * mapa->velicina) + glm::vec2(mapa->velicina), teksturalneKoordinate[2]
		};
		glm::vec4 t4 = {
			pozicija.x * mapa->velicina, mapa->velicina + (pozicija.y * mapa->velicina), teksturalneKoordinate[3]
		};

		return { t1, t2, t3, t4 };
	}
}