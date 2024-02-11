#pragma once

#include <entt/entt.hpp>

namespace ui
{

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

}