#include "OCT/Utilities.h"
using namespace OCT;

s64 IDGenerator::generateID()
{
	static s64 id = 0;
	return id++;
}

s64 IDGenerator::generateIDLib()
{
	static s64 id = 0;
	return id++;
}