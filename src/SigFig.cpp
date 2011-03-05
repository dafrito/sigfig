#include "SigFig.h"
#include <algorithm>
#include <cmath>

using namespace std;

SigFig SigFig::unit() const
{
	return SigFig(pow(10, _precision), _precision);
}

short SigFig::signum() const
{
	return _value > 0 ? 1 : -1;
}

///
// Return the closest value that represents the exact portion of this significant figure.
double SigFig::value() const
{
	double estimated_value = fmod(_value, pow(10, _precision));
	double greatest_digit = abs(floor(
		estimated_value / pow(10, _precision - 1)
	));
	double best_value = _value - estimated_value;
	if (greatest_digit >= 5)
		best_value += this->signum() * pow(10, _precision);
	return best_value;
}

///
// Determine whether two significant figures are equal.
//
// Equivalent values will have an equal "exact" portion and an
// equal precision.
//
// Trivially equal:
// 10.0 == 10.0
//
// Equal with unequal fuzz:
// 10.0 == 10.1
//
// Unequal, due to unequal exact portions:
// 10.0 == 11.0
//
// Unequal, due to unequal precision:
// 10.0 != 10.00
bool SigFig::operator==(const SigFig& other) const
{
	if (_precision != other._precision)
		return false;
	return abs(_value - other._value) < pow(10, _precision);
}

SigFig SigFig::operator+(const SigFig& other) const
{
	return SigFig(_value + other._value, min(_precision, other._precision));
}

SigFig SigFig::operator-(const SigFig& other) const
{
	return SigFig(_value - other._value, min(_precision, other._precision));
}

const SigFig& SigFig::operator+=(const SigFig& other)
{
	_value += other._value;
	_precision = min(_precision, other._precision);
	return *this;
}

const SigFig& SigFig::operator-=(const SigFig& other)
{
	_value -= other._value;
	_precision = min(_precision, other._precision);
	return *this;
}

SigFig& SigFig::operator++()
{
	SigFig u=this->unit();
	*this += u;
	return *this;
}

SigFig SigFig::operator++(int) const
{
	SigFig u=this->unit();
	return *this + u;
}

SigFig& SigFig::operator--()
{
	SigFig u=this->unit();
	*this -= u;
	return *this;
}

SigFig SigFig::operator--(int) const
{
	SigFig u=this->unit();
	return *this - u;
}
