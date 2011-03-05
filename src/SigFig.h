#ifndef PHYSICS_SIGFIG_H
#define PHYSICS_SIGFIG_H

class SigFig
{
private:
	double _value;
	int _precision;

	SigFig() : _value(0), _precision(0) {}

protected:
	static void _multiply(SigFig& out, const SigFig& a, const SigFig& b);
	static void _add(SigFig& out, const SigFig& a, const SigFig& b);
	static void _subtract(SigFig& out, const SigFig& a, const SigFig& b);
	static void _divide(SigFig& out, const SigFig& a, const SigFig& b);
public:
	SigFig(double value) : 
		_value(value), _precision(0) {}
	SigFig(double value, long precision) : 
		_value(value), _precision(precision) {}

	bool operator==(const SigFig& other) const;
	bool operator!=(const SigFig& other) const;
	SigFig operator+(const SigFig& other) const;
	SigFig operator-(const SigFig& other) const;
	SigFig operator*(const SigFig& other) const;
	SigFig operator/(const SigFig& other) const;
	const SigFig& operator+=(const SigFig& other);
	const SigFig& operator-=(const SigFig& other);
	const SigFig& operator*=(const SigFig& other);
	const SigFig& operator/=(const SigFig& other);

	SigFig operator-() const;

	SigFig& operator++();
	SigFig operator++(int) const;

	SigFig& operator--();
	SigFig operator--(int) const;

	bool operator<(const SigFig& other) const;
	bool operator<=(const SigFig& other) const;
	bool operator>(const SigFig& other) const;
	bool operator>=(const SigFig& other) const;

	double value() const;
	short sign() const;
	int sigfigs() const;
	const SigFig unit() const;
};

#endif
