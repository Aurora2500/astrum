#pragma once

#include <vector>
#include <memory>

#include "planet.hpp"

namespace core {

enum class StarType
{
	YellowDwarf,
	RedGiant,
	BlueGiant,
	WhiteDwarf,
	NeutronStar,
};

class Star
{
private:
	StarType m_type;
	int m_seed;
	float m_size;
	std::vector<Planet> m_planets;

public:
	Star(StarType type, int seed, float size);

	inline int seed() const { return m_seed; }
	inline float size() const { return m_size; }
	inline const std::vector<Planet> &planets() const { return m_planets; }
};

}