#pragma once
#include "appstate.hpp"

class MenuState : public AppState
{

public:
	MenuState();
	~MenuState();

	AppStateChange update() override;
};
