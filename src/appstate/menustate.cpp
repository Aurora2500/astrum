#include "menustate.hpp"

MenuState::MenuState()
{
}

MenuState::~MenuState()
{
}

AppStateChange MenuState::update()
{
	return AppStateChange::nop();
}
