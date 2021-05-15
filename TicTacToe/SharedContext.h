#pragma once
#include "Window.h"

struct SharedContext {
	SharedContext()
		:m_wind(nullptr),
		m_eventManager(nullptr) {}
	Window* m_wind;
	EventManager* m_eventManager;
};