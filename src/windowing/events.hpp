#pragma once

#include <vector>

enum class EventKind
{
	KeyDown,
	KeyUp,
	MouseDown,
	MouseUp,
};

struct KeyDownEvent
{
	EventKind kind;
	int key;
};

struct KeyUpEvent
{
	EventKind kind;
	int key;
};

struct Event
{
	EventKind kind;
	union
	{
		KeyDownEvent key_down;
		KeyUpEvent key_up;
	};
};


struct MouseState
{
	bool down;

};

class EventManager
{
private:
	std::vector<Event> m_events;

public:
	EventManager() = default;

	void poll();
	
};