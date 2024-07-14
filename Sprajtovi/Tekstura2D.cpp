#include "Tekstura2D.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace pexel
{
    Tekstura2D::Tekstura2D(const char* fajl, bool flipVertikalno)
    {
        glGenTextures(1, &this->tekstura);
        glBindTexture(GL_TEXTURE_2D, this->tekstura);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

        int komponente;
        stbi_set_flip_vertically_on_load(flipVertikalno);
        uint8_t* podaci = stbi_load(fajl, &this->sirina, &this->visina, &komponente, 0);
        if (!podaci)
        {
            std::cerr << "Tekstura " << fajl << " nije ucitana!\n";
            return;
        }

        std::pair<int, int> formati;
        switch (komponente)
        {
            case 3: formati = { GL_RGB8, GL_RGB };
                break;
            case 4: formati = { GL_RGBA8, GL_RGBA };
                break;
        }

        glTexImage2D(GL_TEXTURE_2D, 0, formati.first, this->sirina, this->visina, 0, formati.second, GL_UNSIGNED_BYTE, podaci);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    Tekstura2D::~Tekstura2D() { glDeleteTextures(1, &this->tekstura); }

    const int Tekstura2D::Sirina() const { return this->sirina; }

    const int Tekstura2D::Visina() const { return this->visina; }

    void Tekstura2D::Povezi(uint32_t slot) const
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, this->tekstura);
    }

    void Tekstura2D::NePovezi() const
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}