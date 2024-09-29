#pragma once
#include "BigInt.h"

class Integer :public BigInt
{
public:
	friend class NumberObject;
	Integer() { setType(0); }
	Integer(const char* rhs) { setType(0); setDigits(string(rhs)); }

	void operator=(BigInt&);
	void operator=(const char* rhs);

	friend ostream& operator<<(ostream&, Integer&);
	friend istream& operator>>(istream&, Integer&);
};

class Decimal :public BigInt
{
public:
	Decimal() { setType(1); }
	Decimal(const char* rhs) { setType(1); setDigits(string(rhs)); }
	void operator=(BigInt&);
	void operator=(const char* rhs);
	friend ostream& operator<<(ostream&, Decimal&);
	friend istream& operator>>(istream&, Decimal&);
};