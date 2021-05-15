#pragma once
#include <SFML/Graphics.hpp>

enum SquareState {
	Empty,
	Circle,
	X,
};

class Square : public sf::Sprite {
public:
	Square();
	~Square();

	void SetState(SquareState);
	SquareState GetState();

private:
	SquareState state;
};