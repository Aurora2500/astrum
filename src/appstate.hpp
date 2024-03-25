#pragma once

#include <atomic>
#include <memory>
#include <vector>
#include <thread>

class AppState;

enum class AppStateChangeType
{
	Nop,
	Push,
	Pop,
	Swap,
};

class AppStateChange
{
private:
	AppStateChangeType m_type;
	std::unique_ptr<AppState> m_next;

	AppStateChange(AppState* next, AppStateChangeType type);
public:
	static AppStateChange nop();
	static AppStateChange push(AppState *next);
	static AppStateChange pop();
	static AppStateChange swap(AppState *next);

friend class AppStateManager;
};


class AppState
{

public:
	virtual ~AppState() = default;
	virtual AppStateChange update() = 0;
};

class AppStateManager
{
private:
	std::vector<std::unique_ptr<AppState>> m_stack;

public:
	AppStateManager();

	bool update();
};