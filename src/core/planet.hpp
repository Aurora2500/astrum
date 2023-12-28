#pragma once

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

public:
	Planet(PlanetType type, int seed);

	inline PlanetType type() const { return m_type; }
	inline int seed() const { return m_seed; }
	inline float size() const { return m_size; }	
};

}
