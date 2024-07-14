#pragma once
#include <memory>

namespace pexel
{
	template<typename T>
	using Objekat = std::shared_ptr<T>;

	template<typename T, typename... Argumenti>
	constexpr Objekat<T> KreirajObjekat(Argumenti&&... argumenti)
	{
		return std::make_shared<T>(std::forward<Argumenti>(argumenti)...);
	}

	template<typename T>
	constexpr bool ObjekatValidan(Objekat<T>& objekat) { return bool(objekat); }
}