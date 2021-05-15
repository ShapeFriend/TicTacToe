#include "Square.h"

Square::Square()
{
}
Square::~Square(){}

void Square::SetState(SquareState new_state)
{
	state = new_state;
}

SquareState Square::GetState()
{
	return state;
}
