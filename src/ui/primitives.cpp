#include "primitives.hpp"

#include <glm/ext.hpp>

namespace ui {

glm::mat4 GlobalProps::screen_mat() const
{
	return glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f);
}

}