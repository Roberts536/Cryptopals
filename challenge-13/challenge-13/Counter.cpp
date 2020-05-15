#include "Counter.h"

int Counter::next()
{
	current += 1;
	return current - 1;
}
