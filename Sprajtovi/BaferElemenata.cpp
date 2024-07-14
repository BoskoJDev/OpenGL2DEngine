#include "BaferElemenata.h"

namespace pexel
{
	BaferElemenata::BaferElemenata()
	{
		glGenVertexArrays(1, &this->VAO);
		glGenBuffers(1, &this->VBO);
		glGenBuffers(1, &this->EBO);
	}

	BaferElemenata::~BaferElemenata()
	{
		glDeleteBuffers(1, &this->EBO);
		glDeleteBuffers(1, &this->VBO);
		glDeleteVertexArrays(1, &this->VAO);
	}

	void BaferElemenata::Crtaj(int brojIndica, uint32_t tipIndica)
	{
		glBindVertexArray(this->VAO);
		glDrawElements(GL_TRIANGLES, brojIndica, tipIndica, nullptr);
		glBindVertexArray(0);
	}

	void BaferElemenata::PodesiPodPodatke(void* podaci, int velicinaPodataka, int ofset)
	{
		glBindVertexArray(this->VAO);
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferSubData(GL_ARRAY_BUFFER, ofset, velicinaPodataka, podaci);
		}
		glBindVertexArray(0);
	}

	void BaferElemenata::PodesiAtributeTemena(int indeks, int velicina, uint32_t tip, int velicinaPodataka, const void* ofset)
	{
		glBindVertexArray(this->VAO);
		{
			glEnableVertexAttribArray(indeks);
			glVertexAttribPointer(indeks, velicina, tip, GL_FALSE, velicinaPodataka, ofset);
		}
		glBindVertexArray(0);
	}

	void BaferElemenata::PodesiPodatke(void* podaci, int velicinaPodataka, uint32_t tipIscrtavanja, void* indice, int velicinaIndica, uint32_t tipIscrtavanjaIndica)
	{
		glBindVertexArray(this->VAO);
		{
			glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
			glBufferData(GL_ARRAY_BUFFER, velicinaPodataka, podaci, tipIscrtavanja);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, velicinaIndica, indice, tipIscrtavanjaIndica);
		}
		glBindVertexArray(0);
	}
}