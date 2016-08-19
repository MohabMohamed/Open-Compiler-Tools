#include "Position.h"
using namespace CT;

const Position Position::invalid = Position(false);

Position::Position(bool valid)
:isValid(valid)
{}

Position::Position(u64 Row, u64 Col)
:row(Row), col(Col), isValid(true)
{}

Position::Position()
:row(0), col(0), isValid(true)
{
}
