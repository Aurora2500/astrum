#include "gamestate.hpp"

GameState::GameState()
{
}

GameState::~GameState()
{
}

AppStateChange GameState::update()
{
	return AppStateChange::nop();
}
