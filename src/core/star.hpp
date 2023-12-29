#pragma once

#include <vector>
#include <memory>

#include <glm/glm.hpp>

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

	glm::vec3 m_position;

public:
	Star(StarType type, int seed, float size, glm::vec3 pos);

	inline int seed() const { return m_seed; }
	inline float size() const { return m_size; }
	inline const glm::vec3 &pos() const { return m_position; }
	inline std::vector<Planet> &planets() { return m_planets; }
	inline const std::vector<Planet> &planets() const { return m_planets; }
};

}