#include "Board.h"

Board::Board()
{
	texture_empty.loadFromFile("EmptySquare.png");
	texture_circle.loadFromFile("CircleSquare.png");
	texture_x.loadFromFile("XSquare.png");

	ClearBoard();
}
Board::~Board(){}

void Board::PositionBoard(sf::Vector2u l_window_size)
{
	sf::Vector2u l_board_center(l_window_size.x / 2, l_window_size.y / 2);
	sf::Vector2u grid_origin;
	grid_origin.x = l_board_center.x - 110;
	grid_origin.y = l_board_center.y - 110;

	for (int i = 0; i < 9; ++i)
	{
		grid[i].setPosition(grid_origin.x + (i % 3) * 75, grid_origin.y + (i / 3) * 75);
	}
}

void Board::ClearBoard()
{
	for (int i = 0; i < 9; ++i)
	{
		SetSquare(grid[i], SquareState::Empty);
	}
}

void Board::EvaluateState()
{
	SquareState l_sqstate = SquareState::Empty;
	if ((grid[0].GetState() == grid[4].GetState() && grid[4].GetState() == grid[8].GetState()) ||
		(grid[2].GetState() == grid[4].GetState() && grid[4].GetState() == grid[6].GetState()))
	{
		l_sqstate = grid[4].GetState();
	}
	else {
		for (int i = 0; i < 3; ++i) {
			if (!(grid[i].GetState() == SquareState::Empty) && grid[i].GetState() == grid[i + 3].GetState() && grid[i].GetState() == grid[i + 6].GetState())
			{
				l_sqstate = grid[i].GetState();
				break;
			}
			if (!(grid[i*3].GetState() == SquareState::Empty) && grid[i*3].GetState() == grid[i*3 + 1].GetState() && grid[i*3].GetState() == grid[i*3 + 2].GetState())
			{
				l_sqstate = grid[i * 3].GetState();
				break;
			}
		}
	}
	switch (l_sqstate) {
	case SquareState::Empty:
		board_state = BoardState::Normal;

		for (int i = 0; i < 9; ++i)
		{
			if (grid[i].GetState() == SquareState::Empty)
			{
				break;
			}
			if (i == 8) {
				board_state = BoardState::Tie;
			}
		}
		break;
	case SquareState::X:
		board_state = BoardState::XWin;
		break;
	case SquareState::Circle:
		board_state = BoardState::CircleWin;
		break;
	default:
		break;
	}
}

BoardState Board::GetState()
{
	return board_state;
}

void Board::SetState(BoardState l_state)
{
	board_state = l_state;
}

void Board::SetSquare(Square &l_sq, SquareState sq_state)
{
	l_sq.SetState(sq_state);
	switch (sq_state) {
	case SquareState::Empty:
		l_sq.setTexture(texture_empty);
		break;
	case SquareState::X:
		l_sq.setTexture(texture_x);
		break;
	case SquareState::Circle:
		l_sq.setTexture(texture_circle);
	default:
		break;
	}
}
