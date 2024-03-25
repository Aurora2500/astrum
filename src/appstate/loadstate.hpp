#pragma once
#include "appstate.hpp"

class LoadingState : public AppState
{
private:
	std::atomic<bool> m_done;
	std::thread m_loader;

public:
	LoadingState();
	~LoadingState();

	AppStateChange update() override;	
};
