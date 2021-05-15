#include "State_MainMenu.h"
#include "StateManager.h"

State_MainMenu::State_MainMenu(StateManager* l_stateManager)
	: BaseState(l_stateManager) {}
State_MainMenu::~State_MainMenu() {}

void State_MainMenu::OnCreate() {
	sf::Vector2u windowSize = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow()->getSize();

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setString(sf::String("Tic Tac Toe"));
	m_text.setCharacterSize(18);

	sf::FloatRect textRect = m_text.getLocalBounds();
	m_text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
	m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 4);

	m_buttonSize = sf::Vector2f(300.0f, 32.0f);
	m_buttonPos = sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2);
	m_buttonPadding = 6; // 4px.

	std::string str[2];
	str[0] = "New Local Game";
	str[1] = "Exit";

	for (int i = 0; i < 2; ++i) {
		sf::Vector2f buttonPosition(m_buttonPos.x, m_buttonPos.y +
			(i * (m_buttonSize.y + m_buttonPadding)));
		m_rects[i].setSize(m_buttonSize);
		m_rects[i].setFillColor(sf::Color::White);
		m_rects[i].setOrigin(m_buttonSize.x / 2.0f,
			m_buttonSize.y / 2.0f);
		m_rects[i].setPosition(buttonPosition);
		m_labels[i].setFont(m_font);
		m_labels[i].setString(sf::String(str[i]));
		m_labels[i].setCharacterSize(12);
		m_labels[i].setFillColor(sf::Color::Black);
		sf::FloatRect rect = m_labels[i].getLocalBounds();
		m_labels[i].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
		m_labels[i].setPosition(buttonPosition);
	}

	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->AddCallback(StateType::MainMenu, "Mouse_Left",
		&State_MainMenu::MouseClick, this);
	evMgr->AddCallback(StateType::MainMenu, "Key_SpaceBar",
		&State_MainMenu::Play, this);
	evMgr->AddCallback(StateType::MainMenu, "Key_1",
		&State_MainMenu::Play, this);
	evMgr->AddCallback(StateType::MainMenu, "Key_Escape",
		&State_MainMenu::Exit, this);
	evMgr->AddCallback(StateType::MainMenu, "Key_2",
		&State_MainMenu::Exit, this);	
}

void State_MainMenu::OnDestroy() {
	EventManager* evMgr = m_stateMgr->
		GetContext()->m_eventManager;
	evMgr->RemoveCallback(StateType::MainMenu, "Mouse_Left");
	evMgr->RemoveCallback(StateType::MainMenu, "Key_SpaceBar");
	evMgr->RemoveCallback(StateType::MainMenu, "Key_Escape");
	evMgr->RemoveCallback(StateType::MainMenu, "Key_1");
	evMgr->RemoveCallback(StateType::MainMenu, "Key_2");
}

void State_MainMenu::Activate() {
	if (m_stateMgr->HasState(StateType::Game)
		&& m_labels[0].getString() == "New Local Game")
	{
		m_labels[0].setString(sf::String("Resume Local Game"));
		sf::FloatRect rect = m_labels[0].getLocalBounds();
		m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
			rect.top + rect.height / 2.0f);
	}
}
void State_MainMenu::Deactivate() {}
void State_MainMenu::Update(const sf::Time& l_time) {}

void State_MainMenu::MouseClick(EventDetails* l_details) {
	sf::Vector2i mousePos = l_details->m_mouse;

	float halfX = m_buttonSize.x / 2.0f;
	float halfY = m_buttonSize.y / 2.0f;
	for (int i = 0; i < 2; ++i) {
		if (mousePos.x >= m_rects[i].getPosition().x - halfX &&
			mousePos.x <= m_rects[i].getPosition().x + halfX &&
			mousePos.y >= m_rects[i].getPosition().y - halfY &&
			mousePos.y <= m_rects[i].getPosition().y + halfY)
		{
			if (i == 0) {
				State_MainMenu::Play(l_details);
			}
			else if (i == 1) {
				State_MainMenu::Exit(l_details);
			}
		}
	}
}

void State_MainMenu::Play(EventDetails * l_details)
{
	m_stateMgr->SwitchTo(StateType::Game);
}

void State_MainMenu::Exit(EventDetails* l_details) {
	m_stateMgr->GetContext()->m_wind->Close(l_details);
}

void State_MainMenu::Draw() {
	sf::RenderWindow* window = m_stateMgr->GetContext()->
		m_wind->GetRenderWindow();
	window->draw(m_text);
	for (int i = 0; i < 2; ++i) {
		window->draw(m_rects[i]);
		window->draw(m_labels[i]);
	}
}