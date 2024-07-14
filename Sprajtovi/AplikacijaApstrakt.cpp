#include "AplikacijaApstrakt.h"
#include <Windows.h>

namespace pexel
{
	AplikacijaApstrakt::AplikacijaApstrakt()
	{
		if (!glfwInit())
			Terminiraj("GLFW nije inicijalizovan!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		
		const GLFWvidmode* videoMod = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, videoMod->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, videoMod->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, videoMod->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, videoMod->refreshRate);

		this->sirinaProzora = videoMod->width;
		this->visinaProzora = videoMod->height;

		this->prozor = glfwCreateWindow(this->sirinaProzora, this->visinaProzora, "", monitor, nullptr);
		if (!this->prozor)
			Terminiraj("Neuspelo kreiranje prozora!");

		glfwMakeContextCurrent(this->prozor);
		glfwSetFramebufferSizeCallback(this->prozor, [](GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); });

		if (glewInit() != GLEW_OK)
			Terminiraj("GLEW nije inicijalizovan!");

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if _DEBUG
		/*Omogucavanje debagovanja u OpenGL-u i postavljanje funkcije za debagovanje*/
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		glDebugMessageCallback(DebugFunkcija, nullptr);
#endif

		// Sakrivanje konzole u 'Release' konfiguraciji
#if !_DEBUG
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
	}

	AplikacijaApstrakt::AplikacijaApstrakt(int _sirinaProzora, int _visinaProzora, int xPozicija, int yPozicija)
		: sirinaProzora(_sirinaProzora), visinaProzora(_visinaProzora)
	{
		if (!glfwInit())
			Terminiraj("GLFW nije inicijalizovan!");

		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		this->prozor = glfwCreateWindow(this->sirinaProzora, this->visinaProzora, "", nullptr, nullptr);
		if (!this->prozor)
			Terminiraj("Neuspelo kreiranje prozora!");

		glfwSetWindowPos(this->prozor, xPozicija, yPozicija);
		glfwMakeContextCurrent(this->prozor);
		glfwSetFramebufferSizeCallback(this->prozor, [](GLFWwindow*, int w, int h) { glViewport(0, 0, w, h); });

		if (glewInit() != GLEW_OK)
			Terminiraj("GLEW nije inicijalizovan!");

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#if _DEBUG
		/*Omogucavanje debagovanja u OpenGL-u i postavljanje funkcije za debagovanje*/
		glEnable(GL_DEBUG_OUTPUT);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
		glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
		glDebugMessageCallback(DebugFunkcija, nullptr);
#endif

// Sakrivanje konzole u 'Release' konfiguraciji
#if !_DEBUG
		ShowWindow(GetConsoleWindow(), SW_HIDE);
#endif
	}

	GLFWwindow* AplikacijaApstrakt::Prozor() const { return this->prozor; }

	void AplikacijaApstrakt::Pokreni(VSync fpsOgranicenje)
	{
		if (!this->Postavke())
			Terminiraj("Greska u ucitavanju!");

		float deltaVreme, trenutnoVreme = float(glfwGetTime());
		glfwSwapInterval(int(fpsOgranicenje));

		while (!glfwWindowShouldClose(this->prozor))
		{
			float vreme = float(glfwGetTime());
			deltaVreme = vreme - trenutnoVreme;
			trenutnoVreme = vreme;

			glfwSetWindowTitle(this->prozor, ("Pexel pogon; FPS: " + std::to_string(int(1 / deltaVreme))).c_str());

			glClear(GL_COLOR_BUFFER_BIT);

			if (!this->Azuriranje(deltaVreme))
				break;

			glfwSwapBuffers(this->prozor);
			glfwPollEvents();
		}

		if (!this->OslobadjanjeResursa())
			Terminiraj("Greska u oslobadjanju resursa!");

		Terminiraj();
	}

	void AplikacijaApstrakt::Terminiraj(const char* poruka)
	{
		if (poruka)
		{
			std::cout << poruka << '\n';
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		glfwTerminate();
	}

	void AplikacijaApstrakt::DebugFunkcija(uint32_t izvor, uint32_t tip, uint32_t id, uint32_t ozbiljnost, int duzina, const char* poruka, const void*)
	{
		// ignorisanje nevaznih upozorenja
		if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

		std::cout << "---------------" << std::endl;
		std::cout << "Debug poruka (" << id << "): " << poruka << std::endl;

		switch (izvor)
		{
			case GL_DEBUG_SOURCE_API: std::cout << "Izvor: API\n";
				break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM: std::cout << "Izvor: Sistem Prozora\n";
				break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Izvor: Kopajler Sejdera\n";
				break;
			case GL_DEBUG_SOURCE_THIRD_PARTY: std::cout << "Izvor: Spoljasnja biblioteka\n";
				break;
			case GL_DEBUG_SOURCE_APPLICATION: std::cout << "Izvor: Aplikacija\n";
				break;
			case GL_DEBUG_SOURCE_OTHER: std::cout << "Izvor: Drugo\n";
				break;
		}

		switch (tip)
		{
			case GL_DEBUG_TYPE_ERROR: std::cout << "Tip: Greska\n";
				break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Tip: Prastaro ponasanje\n";
				break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: std::cout << "Tip: Nedefinisano ponasanje\n";
				break;
			case GL_DEBUG_TYPE_PORTABILITY: std::cout << "Tip: Portabilnost\n";
				break;
			case GL_DEBUG_TYPE_PERFORMANCE: std::cout << "Tip: Perfomanse\n";
				break;
			case GL_DEBUG_TYPE_MARKER: std::cout << "Tip: Marker\n";
				break;
			case GL_DEBUG_TYPE_PUSH_GROUP: std::cout << "Tip: 'Push' grupa\n";
				break;
			case GL_DEBUG_TYPE_POP_GROUP: std::cout << "Tip: 'Pop' grupa\n";
				break;
			case GL_DEBUG_TYPE_OTHER: std::cout << "Tip: drugo\n";
				break;
		}

		switch (ozbiljnost)
		{
			case GL_DEBUG_SEVERITY_HIGH: std::cout << "Ozbiljnost: VELIKA!\n";
				break;
			case GL_DEBUG_SEVERITY_MEDIUM: std::cout << "Ozbiljnost: Srednja\n";
				break;
			case GL_DEBUG_SEVERITY_LOW: std::cout << "Ozbiljnost: niska\n";
				break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Ozbiljnost: Obavestenje\n";
				break;
		}

		std::cout << "--------------------------------------------------------------\n";
	}
}