#include "planet.hpp"

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace core {


Planet::Planet(PlanetType type, int seed, glm::vec3 pos) : m_type(type), m_seed(seed), m_size(1.0f), m_pos(pos)
{
}

}