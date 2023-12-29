#include "star.hpp"

namespace core {

Star::Star(StarType type, int seed, float size, glm::vec3 pos) : m_type(type), m_seed(seed), m_size(size), m_position(pos) {}

}