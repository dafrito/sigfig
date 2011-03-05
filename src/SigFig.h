#ifndef PHYSICS_SIGFIG_H
#define PHYSICS_SIGFIG_H

class SigFig
{
private:
	double _value;
	long _precision;
public:
	SigFig(double value) : 
		_value(value), _precision(0) {}
	SigFig(double value, long precision) : 
		_value(value), _precision(precision) {}

	bool operator==(const SigFig& other) const;
	SigFig operator+(const SigFig& other) const;
	SigFig operator-(const SigFig& other) const;
	const SigFig& operator+=(const SigFig& other);
	const SigFig& operator-=(const SigFig& other);

	SigFig& operator++();
	SigFig operator++(int) const;

	SigFig& operator--();
	SigFig operator--(int) const;

	double value() const;
	short signum() const;
	SigFig unit() const;
};


#endif
