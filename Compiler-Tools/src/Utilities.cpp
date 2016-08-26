#include "Utilities.h"
using namespace CT;

u64 IDGenerator::generateID()
{
	static u64 id = 0;
	return id++;
}