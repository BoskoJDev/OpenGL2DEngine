#include "Sejder.h"

namespace pexel
{
	Sejder::Sejder(const char* vertex_sejder, const char* fragment_sejder)
	{
		const std::string& vs = UcitajSejder(vertex_sejder);
		const std::string& fs = UcitajSejder(fragment_sejder);

		this->program = KreirajSejder(vs, fs);
	}

	Sejder::~Sejder() { glDeleteProgram(this->program); }

	void Sejder::Koristi() { glUseProgram(this->program); }

	void Sejder::NeKoristi() { glUseProgram(0); }

	void Sejder::SetInt(std::string_view naziv, int vrednost)
	{
		glUniform1i(GetLokacijaUniforma(naziv), vrednost);
	}

	void Sejder::SetFloat(std::string_view naziv, float vrednost)
	{
		glUniform1f(GetLokacijaUniforma(naziv), vrednost);
	}

	void Sejder::SetUnsignedInt(std::string_view naziv, unsigned int vrednost)
	{
		glUniform1ui(GetLokacijaUniforma(naziv), vrednost);
	}

	void Sejder::SetDouble(std::string_view naziv, double vrednost)
	{
		glUniform1d(GetLokacijaUniforma(naziv), vrednost);
	}

	void Sejder::SetBool(std::string_view naziv, bool vrednost)
	{
		glUniform1i(GetLokacijaUniforma(naziv), int(vrednost));
	}

	void Sejder::SetVec2(std::string_view naziv, const glm::vec2& vektor)
	{
		glUniform2fv(GetLokacijaUniforma(naziv), 1, glm::value_ptr(vektor));
	}

	void Sejder::SetVec2(std::string_view naziv, float x, float y)
	{
		glUniform2f(GetLokacijaUniforma(naziv), x, y);
	}

	void Sejder::SetVec3(std::string_view naziv, const glm::vec3& vektor)
	{
		glUniform3fv(GetLokacijaUniforma(naziv), 1, glm::value_ptr(vektor));
	}

	void Sejder::SetVec3(std::string_view naziv, float x, float y, float z)
	{
		glUniform3f(GetLokacijaUniforma(naziv), x, y, z);
	}

	void Sejder::SetVec4(std::string_view naziv, const glm::vec4& vektor)
	{
		glUniform4fv(GetLokacijaUniforma(naziv), 1, glm::value_ptr(vektor));
	}

	void Sejder::SetVec4(std::string_view naziv, float x, float y, float z, float w)
	{
		glUniform4f(GetLokacijaUniforma(naziv), x, y, z, w);
	}

	void Sejder::SetMat2(std::string_view naziv, const glm::mat2& mat, unsigned char transponuj)
	{
		glUniformMatrix2fv(GetLokacijaUniforma(naziv), 1, transponuj, glm::value_ptr(mat));
	}

	void Sejder::SetMat3(std::string_view naziv, const glm::mat3& mat, unsigned char transponuj)
	{
		glUniformMatrix3fv(GetLokacijaUniforma(naziv), 1, transponuj, glm::value_ptr(mat));
	}

	void Sejder::SetMat4(std::string_view naziv, const glm::mat4& mat, unsigned char transponuj)
	{
		glUniformMatrix4fv(GetLokacijaUniforma(naziv), 1, transponuj, glm::value_ptr(mat));
	}

	unsigned int Sejder::KompajlirajSejder(const std::string& sejder, unsigned int tip)
	{
		unsigned int tekstura = glCreateShader(tip);
		const char* src = sejder.c_str();
		glShaderSource(tekstura, 1, &src, nullptr);
		glCompileShader(tekstura);

		int uspeh;
		glGetShaderiv(tekstura, GL_COMPILE_STATUS, &uspeh);

		if (uspeh == GL_FALSE)
		{
			int duzina;
			glGetShaderiv(tekstura, GL_INFO_LOG_LENGTH, &duzina);

			char* poruka = (char*)alloca(duzina * sizeof(char));
			glGetShaderInfoLog(tekstura, duzina, &duzina, poruka);
			std::cout << (tip == GL_VERTEX_SHADER ? "Verteksni" : "Fragmentni") <<
				" sejder se nije iskompajlirao!\n" << poruka;

			glDeleteShader(tekstura);
			return 0;
		}

		return tekstura;
	}

	unsigned int Sejder::KreirajSejder(const std::string& vs, const std::string& fs)
	{
		unsigned int program = glCreateProgram();
		unsigned int verteks_sejder = KompajlirajSejder(vs, GL_VERTEX_SHADER);
		unsigned int fragment_sejder = KompajlirajSejder(fs, GL_FRAGMENT_SHADER);

		glAttachShader(program, verteks_sejder);
		glAttachShader(program, fragment_sejder);
		glLinkProgram(program);
		glValidateProgram(program);

		glDeleteShader(verteks_sejder);
		glDeleteShader(fragment_sejder);

		return program;
	}

	std::string Sejder::UcitajSejder(const char* sejder)
	{
		std::ifstream fajl(sejder);
		std::stringstream tok;
		std::string linija;

		if (fajl.is_open())
			while (std::getline(fajl, linija)) { tok << linija << '\n'; }
		else
			std::cout << sejder << " nije ucitan!\n";

		fajl.close();
		return tok.str();
	}

	int Sejder::GetLokacijaUniforma(std::string_view naziv)
	{
		// Ako promenljiva vec postoji u mapi
		if (mapaUniforma.find(naziv) != mapaUniforma.end()) { return mapaUniforma[naziv]; }

		int lokacija = glGetUniformLocation(this->program, naziv.data());

		if (lokacija == -1)
			std::cout << "Upozorenje - promenljiva " << naziv << " nije pronadjena!\n";

		mapaUniforma[naziv] = lokacija;
		return lokacija;
	}
}