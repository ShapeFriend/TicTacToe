#pragma once
#include "StateManager.h"
#include "SharedContext.h"

class Game {
public:
	Game();
	~Game();

	void Update();
	void Render();
	void LateUpdate();

	sf::Time GetElapsed();
	Window* GetWindow();
private:
	Window m_window;
	sf::Clock Clock;
	sf::Time m_elapsed;
	void RestartClock();

	SharedContext m_context;
	StateManager m_stateManager;
};

