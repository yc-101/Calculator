#include "NumberObject.h"
void Integer::operator=(BigInt& rhs)
{
	setType(0);
	setDigits(rhs.getDigits());
	setSign(rhs.getSign());
	setDotPlace(rhs.getDotPlace());
	checkType();
}

ostream& operator<<(ostream& strm, Integer& rhs)
{
	rhs.checkType();
	if (rhs.getSign() == 1)
		strm << "-";
	strm << rhs.getDigits();
	return strm;
}

istream& operator>>(istream& strm, Integer& rhs)
{
	string to_process;
	getline(strm, to_process);
	rhs.setDigits(to_process);
	rhs.setSign(0);
	rhs.setType(1);
	rhs.setDotPlace(string::npos);
	return strm;
	/*
	string i;
	strm >> i;
	if (i[0] == '-') {
		i.erase(0, 1);
		rhs.setSign(1);
	}
	else
		rhs.setSign(0);

	int dotPt = i.find('.');
	if (dotPt != string::npos)
	{
		i.erase(dotPt);
	}
	rhs.setType(0);
	rhs.setDotPlace(string::npos);
	rhs.setDigits(i);
	rhs.checkType();
	return strm;
	*/
}

void Decimal::operator=(BigInt& rhs)
{
	setType(1);
	setDigits(rhs.getDigits());
	setSign(rhs.getSign());
	setDotPlace(rhs.getDotPlace());
	checkType();
}

void Decimal::operator=(const char* rhs)
{
	setType(1);
	setDigits(string(rhs));
}
void Integer::operator=(const char* rhs)
{
	setType(0);
	setDigits(string(rhs));
}


ostream& operator<<(ostream& strm, Decimal& rhs)
{
	rhs.checkType();
	if (rhs.getSign() == 1)
		strm << "-";
	strm << rhs.getDigits();
	return strm;
}

istream& operator>>(istream& strm, Decimal& rhs)
{
	string to_process;
	getline(strm, to_process);
	rhs.setDigits(to_process);
	rhs.setSign(0);
	rhs.setType(1);
	rhs.setDotPlace(string::npos);
	return strm;
}

BigInt operator+(const Integer i, const Decimal d) { return i + d; }

BigInt operator-(const Integer i, const Decimal d) { return i - d; }

BigInt operator+(const Decimal d, const Integer i) { return d + i; }

BigInt operator-(const Decimal d, const Integer i) { return d - i; }

BigInt operator*(const Integer i, const Decimal d) { return i * d; }

BigInt operator/(const Integer i, const Decimal d) { return i / d; }

BigInt operator*(const Decimal d, const Integer i) { return d * i; }

BigInt operator/(const Decimal d, const Integer i) { return d / i; }