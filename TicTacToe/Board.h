#pragma once
#include "Square.h"

enum BoardState{
	Normal,
	CircleWin,
	XWin,
	Tie
};

class Board
{
public:
	Board();
	~Board();

	void PositionBoard(sf::Vector2u l_window_size);
	void ClearBoard();
	void EvaluateState();

	BoardState GetState();
	void SetState(BoardState);
	void SetSquare(Square &l_sq, SquareState sq_state);

	Square grid[9];
private:
	sf::Texture texture_empty;
	sf::Texture texture_circle;
	sf::Texture texture_x;

	BoardState board_state;
};

