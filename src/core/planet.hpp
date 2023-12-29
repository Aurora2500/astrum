#pragma once

#include <glm/glm.hpp>

namespace core {

enum class PlanetType
{
	Continental,
	Desert,
};

class Planet
{
private:
	PlanetType m_type;
	int m_seed;
	float m_size;
	glm::vec3 m_pos;

public:
	Planet(PlanetType type, int seed, glm::vec3 pos);

	inline PlanetType type() const { return m_type; }
	inline int seed() const { return m_seed; }
	inline float size() const { return m_size; }	
	inline glm::vec3 pos() const { return m_pos; }
};

}
