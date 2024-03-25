#include "loadstate.hpp"
#include "menustate.hpp"

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
