#pragma once

/*
A counter returning an increasing sequence of integers starting from zero with
successive calls to next().
*/
class Counter
{
public:
	Counter() = default;
	int next();

private:
	int current = 0;
};
