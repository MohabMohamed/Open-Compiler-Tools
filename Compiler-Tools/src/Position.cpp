#include "Position.h"
using namespace CT;

const Position Position::Invalid = Position(false);

Position::Position(bool valid)
:isValid(valid)
{}

Position::Position(u64 Row, u64 Col)
:row(Row), col(Col), isValid(true)
{}