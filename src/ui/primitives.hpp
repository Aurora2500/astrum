#pragma once

#include <glm/glm.hpp>

namespace ui
{

struct GlobalProps
{
	int screenWidth;
	int screenHeight;

	glm::mat4 screen_mat() const;
};

enum class AnchorHorizontal
{
	Left,
	Center,
	Right,
};

enum class AnchorVertical
{
	Top,
	Center,
	Bottom,
};

struct Anchor
{
	AnchorHorizontal horizontal;
	AnchorVertical vertical;
};

struct Rect
{
	int x;
	int y;
	int w;
	int h;
};

}