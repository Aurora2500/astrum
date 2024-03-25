#pragma once
#include "primitives.hpp"

namespace ui {

/// @brief  Base class for all UI elements to inherit from.
class BaseUI
{
public:
	virtual void render(GlobalProps props) = 0;
	virtual ~BaseUI() = default;
};

/// @brief  Base class for all UI elements that are appropiate to be contained in another element.
class ContainableUI : public BaseUI
{
public:
	virtual void fit(ui::Rect rect) = 0;
};

}