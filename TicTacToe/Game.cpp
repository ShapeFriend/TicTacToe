#include "Game.h"

Game::Game() : m_window("Tic Tac Toe", sf::Vector2u(500, 400)),
m_stateManager(&m_context) {
	// Setting up class members.
	Clock.restart();
	srand(time(nullptr));

	m_context.m_wind = &m_window;
	m_context.m_eventManager = m_window.GetEventManager();
	//m_stateManager.SwitchTo(StateType::Intro);
	m_stateManager.SwitchTo(StateType::MainMenu);
}

Game::~Game() {}

sf::Time Game::GetElapsed() { return Clock.getElapsedTime(); }
void Game::RestartClock() { m_elapsed = Clock.restart(); }
Window* Game::GetWindow() {	return &m_window; }

void Game::Update() {
	m_window.Update(); // Update window events.
	m_stateManager.Update(m_elapsed);
}
void Game::Render() {
	m_window.BeginDraw();
	m_stateManager.Draw();
	m_window.EndDraw();
}
void Game::LateUpdate() {
	m_stateManager.ProcessRequests();
	RestartClock();
}