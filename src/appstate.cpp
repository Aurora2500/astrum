#include "appstate.hpp"

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
		m_stack.push_back(std::move(change.m_next));
		break;
	case AppStateChangeType::Pop:
		m_stack.pop_back();
		break;
	case AppStateChangeType::Swap:
		m_stack.pop_back();
		m_stack.push_back(std::move(change.m_next));
		break;
	}

	return true;
};

static void load_assets(std::atomic<bool> &done)
{
	// auto &assets = Locator::assets();
	done.store(true, std::memory_order_release);
}

LoadingState::LoadingState()
	: m_done(false)
{
	m_loader = std::thread(load_assets, std::ref(m_done));
}

LoadingState::~LoadingState()
{
}

AppStateChange LoadingState::update()
{
	if (m_done.load(std::memory_order_acquire))
	{
		m_loader.join();
		return AppStateChange::swap(new MenuState());
	}
	return AppStateChange::nop();
}

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

