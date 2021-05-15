#include "State_Game.h"
#include "StateManager.h"

State_Game::State_Game(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}
State_Game::~State_Game() {}

void State_Game::textSetter(sf::Text &m_text, sf::Font &m_font, sf::String m_message, 
	sf::Vector2u &l_windSize)
{
	m_text.setFont(m_font);
	m_text.setString(m_message);
	m_text.setCharacterSize(18);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(l_windSize.x / 2.0f, 5 * l_windSize.y / 6);

	m_text.setFillColor(sf::Color::Red);
}

void State_Game::OnCreate() {

	sf::Vector2u l_windSize = m_stateMgr->GetContext()->
		m_wind->GetWindowSize();
	board.PositionBoard(l_windSize);

	m_font.loadFromFile("arial.ttf");
	textSetter(turn_textp1, m_font, "Player X's Turn", l_windSize);
	textSetter(turn_textp2, m_font, "Player O's Turn", l_windSize);
	textSetter(wintext_x, m_font, "Player X Wins!", l_windSize);
	textSetter(wintext_o, m_font, "Player O Wins!", l_windSize);
	textSetter(wintext_tie, m_font, "It's a Tie!", l_windSize);

	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::Game, "Mouse_Left",
		&State_Game::MouseClick, this);
	evMgr->AddCallback(StateType::Game, "Key_Escape",
		&State_Game::MainMenu, this);
	/*evMgr->AddCallback(StateType::Game, "Key_P",
		&State_Game::Pause, this);*/
}

void State_Game::OnDestroy() {
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::Game, "Key_Escape");
	evMgr->RemoveCallback(StateType::Game, "Mouse_Left");
	/*evMgr->RemoveCallback(StateType::Game, "Key_P");*/
}

void State_Game::Activate() {}
void State_Game::Deactivate() {}

void State_Game::Update(const sf::Time& l_time) {}

void State_Game::Draw() {
	sf::RenderWindow* window = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow();

	for (int i = 0; i < 9; ++i)
	{
		window->draw(board.grid[i]);
	}

	switch (board.GetState()) {
	case BoardState::Normal:
		if (player2_turn) {
			window->draw(turn_textp2);
		}
		else {
			window->draw(turn_textp1);
		}
		break;
	case BoardState::CircleWin:
		window->draw(wintext_o);
		break;
	case BoardState::XWin:
		window->draw(wintext_x);
		break;
	case BoardState::Tie:
		window->draw(wintext_tie);
	default:
		break;
	}
}

void State_Game::MainMenu(EventDetails* l_details) {
	m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::MouseClick(EventDetails* l_details) {
	sf::Vector2i mousePos = l_details->m_mouse;

	if (!(board.GetState() == BoardState::Normal))
	{
		board.ClearBoard();
		board.SetState(BoardState::Normal);
		player2_turn = false;
		return;
	}

	for (int i = 0; i < 9; ++i) {
		if (mousePos.x >= board.grid[i].getPosition().x &&
			mousePos.x <= board.grid[i].getPosition().x + 70 &&
			mousePos.y >= board.grid[i].getPosition().y &&
			mousePos.y <= board.grid[i].getPosition().y +70 &&
			board.grid[i].GetState() == SquareState::Empty)
		{

			if (player2_turn) {
				board.SetSquare(board.grid[i], SquareState::Circle);
			}
			else {
				board.SetSquare(board.grid[i], SquareState::X);
			}
			player2_turn = !player2_turn;
			
			board.EvaluateState();
		}
	}
}

//void State_Game::Pause(EventDetails* l_details) {
//	m_stateMgr->SwitchTo(StateType::Paused);
//}