#pragma once
#include "appstate.hpp"

class GameState : public AppState
{

public:
	GameState();
	~GameState();

	AppStateChange update() override;
};