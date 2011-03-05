#include "SigFig.h"
#include <algorithm>
#include <cmath>

using namespace std;

const SigFig SigFig::unit() const
{
	return SigFig(pow(10, _precision), _precision);
}

short SigFig::sign() const
{
	if (this->value() == 0)
		return 0;
	return this->value() > 0 ? 1 : -1;
}

int SigFig::sigfigs() const
{
	int leading_place=floor(log10(abs(_value)));
	return max(0, leading_place-_precision+1);
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
		best_value += (_value > 0 ? 1 : -1) * pow(10, _precision);
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

bool SigFig::operator!=(const SigFig& other) const
{
	return !(*this == other);
}

bool SigFig::operator<(const SigFig& other) const
{
	return (*this - other).sign() < 0;
}

bool SigFig::operator<=(const SigFig& other) const
{
	return (*this - other).sign() <= 0;
}

bool SigFig::operator>(const SigFig& other) const
{
	return (*this - other).sign() > 0;
}

bool SigFig::operator>=(const SigFig& other) const
{
	return (*this - other).sign() >= 0;
}

SigFig SigFig::operator-() const
{
	return SigFig(-_value, _precision);
}

void SigFig::_add(SigFig& out, const SigFig& a, const SigFig& b)
{
	// While this looks like we're giving our value "maximum" precision,
	// we're actually losing precision since we're pushing the precision
	// to a bigger value.
	out._value = a._value + b._value;
	out._precision = max(a._precision, b._precision);
}

SigFig SigFig::operator+(const SigFig& other) const
{
	SigFig rv;
	SigFig::_add(rv, *this, other);
	return rv;
}

const SigFig& SigFig::operator+=(const SigFig& other)
{
	SigFig::_add(*this, *this, other);
	return *this;
}

void SigFig::_subtract(SigFig& out, const SigFig& a, const SigFig& b)
{
	out._value = a._value - b._value;
	out._precision = max(a._precision, b._precision);
}

SigFig SigFig::operator-(const SigFig& other) const
{
	SigFig rv;
	SigFig::_subtract(rv, *this, other);
	return rv;
}

const SigFig& SigFig::operator-=(const SigFig& other)
{
	SigFig::_subtract(*this, *this, other);
	return *this;
}

void SigFig::_multiply(SigFig& out, const SigFig& a, const SigFig& b)
{
	int sigfigs = min(a.sigfigs(), b.sigfigs());
	out._value = a._value * b._value;
	int leading_place=floor(log10(abs(out._value)));
	out._precision = leading_place - sigfigs + 1;
}

SigFig SigFig::operator*(const SigFig& other) const
{
	SigFig rv;
	SigFig::_multiply(rv, *this, other);
	return rv;
}

const SigFig& SigFig::operator*=(const SigFig& other)
{
	SigFig::_multiply(*this, *this, other);
	return *this;
}

void SigFig::_divide(SigFig& out, const SigFig& a, const SigFig& b)
{
	int sigfigs = min(a.sigfigs(), b.sigfigs());
	out._value = a._value / b._value;
	int leading_place=floor(log10(abs(out._value)));
	out._precision = leading_place - sigfigs + 1;
}

SigFig SigFig::operator/(const SigFig& other) const
{
	SigFig rv;
	SigFig::_divide(rv, *this, other);
	return rv;
}

const SigFig& SigFig::operator/=(const SigFig& other)
{
	SigFig::_divide(*this, *this, other);
	return *this;
}


SigFig& SigFig::operator++()
{
	SigFig::_add(*this, *this, this->unit());
	return *this;
}

SigFig SigFig::operator++(int) const
{
	SigFig rv;
	SigFig::_add(rv, *this, this->unit());
	return rv;
}

SigFig& SigFig::operator--()
{
	SigFig::_subtract(*this, *this, this->unit());
	return *this;
}

SigFig SigFig::operator--(int) const
{
	SigFig rv;
	SigFig::_subtract(rv, *this, this->unit());
	return rv;
}
