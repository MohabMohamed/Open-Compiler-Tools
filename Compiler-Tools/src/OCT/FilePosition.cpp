#include "OCT/FilePosition.h"
using namespace OCT;

const FilePosition FilePosition::invalid = FilePosition(false);

FilePosition::FilePosition(bool valid)
:isValid(valid)
{}

FilePosition::FilePosition(u64 Row, u64 Col)
:row(Row), col(Col), isValid(true)
{}

FilePosition::FilePosition()
:row(0), col(0), isValid(true)
{
}
