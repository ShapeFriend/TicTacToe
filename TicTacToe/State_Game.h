#pragma once
#include "BaseState.h"
#include "EventManager.h"
#include "Board.h"

class State_Game : public BaseState {
public:
	State_Game(StateManager* l_stateManager);
	~State_Game();

	void textSetter(sf::Text &m_text, sf::Font &m_font, sf::String m_message,
		sf::Vector2u &l_windSize);

	void OnCreate();
	void OnDestroy();

	void Activate();
	void Deactivate();

	void Update(const sf::Time& l_time);
	void Draw();

	void MouseClick(EventDetails* l_details);
	void MainMenu(EventDetails* l_details);
	void Pause(EventDetails* l_details);
private:
	sf::Text turn_textp1;
	sf::Text turn_textp2;
	sf::Text wintext_o;
	sf::Text wintext_x;
	sf::Text wintext_tie;
	sf::Font m_font;
	Board board;
	bool player2_turn = 0;
};