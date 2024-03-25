#pragma once

#include <vector>
#include <memory>

#include "base.hpp"

namespace ui {

enum class Direction
{
	Row,
	Column,
};

struct FlexboxProps
{
	Direction direction;
};

class Flexbox : public ContainableUI
{
private:
	std::vector<std::shared_ptr<ContainableUI>> children;

public:
	Flexbox();
	~Flexbox();

	void fit(ui::Rect rect) override;
	void render() override;

};


}