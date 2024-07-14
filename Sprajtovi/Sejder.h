#pragma once

#include "GLEW/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <iostream>
#include <string_view>

namespace pexel
{
	class Sejder
	{
	public:
		Sejder(const char* vertex_sejder, const char* fragment_sejder);
		~Sejder();

		void Koristi();
		void NeKoristi();

		void SetInt(std::string_view naziv, int vrednost);
		void SetFloat(std::string_view naziv, float vrednost);
		void SetUnsignedInt(std::string_view naziv, unsigned int vrednost);
		void SetDouble(std::string_view naziv, double vrednost);
		void SetBool(std::string_view naziv, bool vrednost);

		void SetVec2(std::string_view naziv, const glm::vec2& vektor);
		void SetVec2(std::string_view naziv, float x, float y);

		void SetVec3(std::string_view naziv, const glm::vec3& vektor);
		void SetVec3(std::string_view naziv, float x, float y, float z);

		void SetVec4(std::string_view naziv, const glm::vec4& vektor);
		void SetVec4(std::string_view naziv, float x, float y, float z, float w);

		void SetMat2(std::string_view naziv, const glm::mat2& mat, unsigned char transponuj = GL_FALSE);
		void SetMat3(std::string_view naziv, const glm::mat3& mat, unsigned char transponuj = GL_FALSE);
		void SetMat4(std::string_view naziv, const glm::mat4& mat, unsigned char transponuj = GL_FALSE);

	private:
		unsigned int program;

		// Sluzice za skladistenje uniformnih promenljivih za koje je upozorenje vec bilo prikazano
		std::unordered_map<std::string_view, int> mapaUniforma;

		unsigned int KreirajSejder(const std::string& vs, const std::string& fs);
		unsigned int KompajlirajSejder(const std::string& sejder, unsigned int tip);

		std::string UcitajSejder(const char* sejder);

		int GetLokacijaUniforma(std::string_view naziv);
	};
}