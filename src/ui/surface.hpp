#pragma once

#include "base.hpp"

namespace ui {

class Surface : public ContainableUI
{
private:
	Rect m_rect;
public:
	Surface();
	virtual ~Surface() override;

	void fit(ui::Rect rect) override;
	virtual void render(GlobalProps props) override;
};

}