#pragma once

#include <iostream>
#include <string> //getline
#include <vector>
#include <cmath>
using namespace std;

class BigInt {
private:
	int type;	//0:Integer	1:Decimal 2:operator
	bool sign;	//0:+		1:-
	string name;
	string digits;
	int dotPlace;


public:
	static vector<BigInt> All; //存所有變數
	BigInt() { name = ""; };
	BigInt(string n) { name = n; };
	BigInt(bool, string, string);//type, name, digits

	void setType(int _type) { type = _type; }
	void setSign(bool _sign) { sign = _sign; }
	void setDigits(string _digits) { digits = _digits; }
	void setDotPlace(int _dotPlace) { dotPlace = _dotPlace; }
	void setName(string _name)
	{
		//清除空格
		int i = 0;
		while (_name[i] == ' ')
			i++;
		_name.erase(0, i);
		i = _name.length() - 1;
		while (_name[i] == ' ')
			i--;
		_name.erase(i + 1, _name.length() - 1);

		name = _name;
	}

	int getType() { return type; }
	bool getSign() { return sign; }
	string getDigits() { return digits; }
	int getDotPlace() { return dotPlace; }
	string getName() { return name; }

	void checkType()
	{
		dotPlace = digits.find('.');

		if (type == 0)
		{
			if (dotPlace != string::npos)
			{
				digits.erase(dotPlace);
				dotPlace = -1;
			}
		}
		else
		{
			if (dotPlace == string::npos)
			{
				dotPlace = digits.length();
				digits += '.';
			}

			if (digits.length() - dotPlace - 1 < 100)//小數部分不足100位
			{
				//補到100位數
				for (int i = digits.length() - dotPlace - 1; i < 100; i++)
					digits += '0';
			}
			else
			{
				digits.erase(dotPlace + 101);
			}
		}
	}

	friend BigInt process(string);
	BigInt operator+(BigInt) const;
	BigInt operator-(BigInt) const;
	BigInt operator*(BigInt) const;
	BigInt operator/(BigInt) const;
	BigInt operator^(BigInt) const;
	void operator=(const BigInt&);
	int compare(string) const; //回傳: -1:<  0:==  1:>
	friend ostream& operator<<(ostream&, const BigInt&);
};
