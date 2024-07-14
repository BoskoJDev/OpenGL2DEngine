#include "Aplikacija.h"

pexel::Objekat<pexel::Sprajt> karta;

bool Aplikacija::Postavke()
{
    karta = pexel::KreirajObjekat<pexel::Sprajt>("karta.jpg", glm::vec2(50.0f, 300.0f),  glm::vec2(100.0f, 100.0f));

    this->unos = pexel::Unos::GetInstanca(this);

    this->ratnica2 = pexel::KreirajObjekat<pexel::Sprajt>("ratnica.png", glm::vec2(50.0f, 300.0f), glm::vec2(50.0f, 450.0f));
    ratnica2->PostavkaAnimacija(1, 9, 16);
    ratnica2->SetBrzinaAnimacije(0, 10.0f);
    ratnica2->PocetniKrajnjiFrejmovi(0, 0, 8, 8, 9);
    ratnica2->SetIndeksAnimacije(0);

    this->kamera = pexel::KreirajObjekat<pexel::Kamera2D>(0.0f, 800.0f, 0.0f, 600.0f);
    this->mapa = pexel::KreirajObjekat<pexel::MapaPlocica>("tilemapa.png", "mapa_plocica.txt", 32, 100.0f);
    this->svetlo = pexel::KreirajObjekat<pexel::Svetlo2D>(glm::vec2(), 100.0f);

    this->ratnica = pexel::KreirajObjekat<pexel::Sprajt>("ratnica.png", glm::vec2(50.0f), glm::vec2(100.0f));
    ratnica->PostavkaAnimacija(8, 9, 16);
    ratnica->SetBrzinaAnimacije(0, 10.0f);
    ratnica->SetBrzinaAnimacije(1, 10.0f);
    ratnica->SetBrzinaAnimacije(2, 10.0f);
    ratnica->SetBrzinaAnimacije(3, 10.0f);
    ratnica->PocetniKrajnjiFrejmovi(0, 0, 7, 8, 8);
    ratnica->PocetniKrajnjiFrejmovi(1, 0, 5, 8, 6);
    ratnica->PocetniKrajnjiFrejmovi(2, 0, 6, 8, 7);
    ratnica->PocetniKrajnjiFrejmovi(3, 0, 4, 8, 5);
    ratnica->PocetniKrajnjiFrejmovi(4, 0, 7, 1, 8);
    ratnica->PocetniKrajnjiFrejmovi(5, 0, 5, 1, 6);
    ratnica->PocetniKrajnjiFrejmovi(6, 0, 6, 1, 7);
    ratnica->PocetniKrajnjiFrejmovi(7, 0, 4, 1, 5);

    return true;
}

bool Aplikacija::Azuriranje(float deltaVreme)
{
    this->ProcesirajTastaturu(deltaVreme);

    auto& matricaKamere = this->kamera->VPMatrica();

    this->mapa->CrtajPlocice(matricaKamere, this->svetlo);
    
    ratnica2->Azuriraj(matricaKamere, deltaVreme, this->svetlo);
    
    this->ratnica->SetPozicija(pozicijaIgraca);
    this->ratnica->Azuriraj(matricaKamere, deltaVreme, this->svetlo);
    
    this->kamera->SetPozicija(pozicijaIgraca.x - 300.0f, pozicijaIgraca.y - 200.0f);
    
    this->svetlo->Crtaj(matricaKamere);

    karta->Azuriraj(matricaKamere, deltaVreme);

    return true;
}

void Aplikacija::ProcesirajTastaturu(float deltaVreme)
{
    pexel::TasterTastature taster = unos->ZadnjiPritisnutTaster();
    switch (taster)
    {
        using enum pexel::TasterTastature;

        case W:
            {
                if (unos->TasterPritisnut(taster))
                {
                    this->pozicijaIgraca.y += 400.0f * deltaVreme;
                    this->ratnica->SetIndeksAnimacije(0);
                }
                else if (unos->TasterPusten(taster))
                {
                    this->ratnica->SetIndeksAnimacije(4);
                }
            }
            break;
        case S:
            {
                if (unos->TasterPritisnut(taster))
                {
                    this->pozicijaIgraca.y -= 400.0f * deltaVreme;
                    this->ratnica->SetIndeksAnimacije(1);
                }
                else if (unos->TasterPusten(taster))
                {
                    this->ratnica->SetIndeksAnimacije(5);
                }
            }
            break;
        case A:
            {
                if (unos->TasterPritisnut(taster))
                {
                    this->pozicijaIgraca.x -= 400.0f * deltaVreme;
                    this->ratnica->SetIndeksAnimacije(2);
                }
                else if (unos->TasterPusten(taster))
                {
                    this->ratnica->SetIndeksAnimacije(6);
                }
            }
            break;
        case D:
            {
                if (unos->TasterPritisnut(taster))
                {
                    this->pozicijaIgraca.x += 400.0f * deltaVreme;
                    this->ratnica->SetIndeksAnimacije(3);
                }
                else if (unos->TasterPusten(taster))
                {
                    this->ratnica->SetIndeksAnimacije(7);
                }
            }
            break;
    }
}
