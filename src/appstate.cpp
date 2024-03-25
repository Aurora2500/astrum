#include "appstate.hpp"
#include "appstate/loadstate.hpp"

#include <iostream>

#include "util/locator.hpp"

AppStateChange::AppStateChange(AppState* next, AppStateChangeType type)
	: m_type(type)
	, m_next(next)
{
}

AppStateChange AppStateChange::nop()
{
	return AppStateChange(nullptr, AppStateChangeType::Nop);
}

AppStateChange AppStateChange::push(AppState *next)
{
	return AppStateChange(next, AppStateChangeType::Push);
}

AppStateChange AppStateChange::pop()
{
	return AppStateChange(nullptr, AppStateChangeType::Pop);
}

AppStateChange AppStateChange::swap(AppState *next)
{
	return AppStateChange(next, AppStateChangeType::Swap);
}

AppStateManager::AppStateManager()
{
	m_stack.emplace_back(new LoadingState());
}

bool AppStateManager::update()
{
	if (m_stack.size() == 0) return false;
	
	AppState &top = *m_stack.back();

	auto change = top.update();

	switch (change.m_type)
	{
	case AppStateChangeType::Nop:
		break;
	case AppStateChangeType::Push:
		std::cout << "Pushing new state" << std::endl;
		m_stack.push_back(std::move(change.m_next));
		break;
	case AppStateChangeType::Pop:
		std::cout << "Popping state" << std::endl;
		m_stack.pop_back();
		break;
	case AppStateChangeType::Swap:
		std::cout << "Swapping state" << std::endl;
		m_stack.pop_back();
		m_stack.push_back(std::move(change.m_next));
		break;
	}

	return true;
};
