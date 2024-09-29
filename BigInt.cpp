#include "BigInt.h"
#include <algorithm>

vector<BigInt> BigInt::All;

string addition(string A, string B);
string subtraction(string A, string B);

BigInt::BigInt(bool t, string n, string d)
{
	this->type = t;
	this->name = n;
	this->digits = d;
	this->dotPlace = digits.find('.');
	if (digits[0] == '-') {
		this->sign = 1;
		digits.erase(0, 1);
	}
	else {
		this->sign = 0;
	}
}

BigInt BigInt::operator+(const BigInt rhs) const
{
	BigInt c;
	bool ansType;
	bool ansSign;
	string ansDigits = "";
	int ansDotPlace;

	if (sign == 0 && rhs.sign == 0) {		// タ+タ
		ansDigits = addition(digits, rhs.digits);
		ansSign = 0;

	}
	else if (sign == 1 && rhs.sign == 1) {		// 璽+璽
		string a = digits;
		//a.erase(0, 1);
		string b = rhs.digits;
		//b.erase(0, 1);
		ansDigits = addition(a, b);		// タ+タ笲衡
		//ansDigits = '-' + ansDigits;		// р璽腹ㄓ
		ansSign = 1;
	}
	else {
		if (sign == 0 && rhs.sign == 1) {		// タ+璽 = タ-タ
			ansDigits = subtraction(digits, rhs.digits);
		}
		else {		//sign == 1 && rhs.sign == 0		//璽+タ = タ-タ
			ansDigits = subtraction(rhs.digits, digits);
		}
		if (ansDigits[0] == '-') {
			ansSign = 1;
			ansDigits.erase(0, 1);
		}
		else {
			ansSign = 0;
		}
	}
	ansDotPlace = ansDigits.find('.');
	if (ansDotPlace != string::npos) {
		ansType = 1;
	}
	else {
		ansType = 0;
	}
	c.type = ansType;
	c.sign = ansSign;
	c.digits = ansDigits;
	c.dotPlace = ansDotPlace;

	return c;
}

BigInt BigInt::operator-(const BigInt rhs) const
{
	BigInt c;
	bool ansType;
	bool ansSign;
	string ansDigits = "";
	int ansDotPlace;

	if (sign == 0 && rhs.sign == 0) {		// タ-タ
		ansDigits = subtraction(digits, rhs.digits);
		if (ansDigits[0] == '-') {
			ansSign = 1;
			ansDigits.erase(0, 1);
		}
		else {
			ansSign = 0;
		}
		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != string::npos) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}
	else if (sign == 1 && rhs.sign == 1) {		// 璽-璽 = 璽(タ-タ)
		string a = digits;
		//a.erase(0, 1);
		string b = rhs.digits;
		//b.erase(0, 1);
		ansDigits = subtraction(a, b);		// タ-タ笲衡
		if (ansDigits[0] == '-') {
			ansDigits.erase(0, 1);			// р璽腹奔
			ansSign = 0;
		}
		else {
			//ansDigits = '-' + ansDigits;		// р璽腹ㄓ
			ansSign = 1;
		}

		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != string::npos) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}
	else {
		string a = digits;
		if (a[0] == '-')
			a.erase(0, 1);
		string b = rhs.digits;
		if (b[0] == '-')
			b.erase(0, 1);

		if (sign == 0 && rhs.sign == 1) {		// タ-璽 = タ+タ
			ansDigits = addition(a, b);
			ansSign = 0;
		}
		else {		//sign == 1 && rhs.sign == 0		//璽-タ = 璽(タ+タ)
			ansDigits = addition(a, b);
			//ansDigits = '-' + ansDigits;
			ansSign = 1;
		}

		ansDotPlace = ansDigits.find('.');
		if (ansDotPlace != string::npos) {
			ansType = 1;
		}
		else {
			ansType = 0;
		}
	}
	if (c.digits[0] == '.')
		c.digits = '0' + c.digits;
	c.type = ansType;
	c.sign = ansSign;
	c.digits = ansDigits;
	c.dotPlace = ansDotPlace;

	return c;
}

BigInt BigInt::operator*(const BigInt rhs) const
{
	BigInt c;
	string ans;
	int decPt;
	int len1 = digits.size();
	int len2 = rhs.digits.size();
	// 101 0s
	string dec_0 = "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";
	// judge ans int or dec
	if (type == 0 && rhs.type == 0) {
		decPt = -1;
		c.type = false;
	}
	else {
		c.type = true;

		if (dotPlace == string::npos) {
			decPt = digits.length() + rhs.dotPlace - 1;
		}

		else if (rhs.dotPlace == string::npos)
			decPt = rhs.digits.length() + dotPlace - 1;

		else
			decPt = dotPlace + rhs.dotPlace;//0.01*0.0123
	}

	if (this->compare("0") == 0 || rhs.compare("0") == 0)
		if (c.type == false)
			ans = "0";
		else
			ans = dec_0;


	else
	{
		if (type && rhs.type)
		{
			len1 -= 50;
			len2 -= 50;
		}

		//vector <int> res(len1 + len2, 0); //  - ((type == 1) ? 1 : 0) - ((rhs.type == 1) ? 1 : 0)
		vector <int> res(len1 + len2, 0);
		int _1 = 0;
		int _2 = 0;
		for (int i = len1 - 1; i >= 0; i--)
		{
			if (digits[i] == '.') continue;

			int cry = 0;
			int n1 = digits[i] - '0';

			// shift pos to l after every multiplication of a digit in rhs
			_2 = 0;
			// go from right to left in rhs
			for (int j = len2 - 1; j >= 0; j--)
			{
				if (rhs.digits[j] == '.') continue;
				// take current digit of second number
				int n2 = rhs.digits[j] - '0';
				// multiply with current digit of 1st num & add res to prev stored res at current pos
				int sum = n1 * n2 + res[_1 + _2] + cry;
				// carry for next iteration
				cry = sum / 10;
				res[_1 + _2] = sum % 10;
				_2++;
			}
			// store carry in next cell
			if (cry > 0)
				res[_1 + _2] += cry;
			// shift pos to left after every multiplication of a digit og       
			_1++;
		}


		// ignore 0s from the right
		//digits.length()-digits.dotPlace = 计
		int q = res.size() - 1;
		if (c.type == 1)
		{
			while (q > 100 && res[q] == 0)
				q--;
			while (q >= 100)
				ans += res[q--] + '0';
			ans += '.';
			while (q >= 0)
				ans += res[q--] + '0';
		}
		else
		{
			while (q >= 0 && res[q] == 0)
				q--;
			while (q >= 0)
				ans += to_string(res[q--]);
		}

		//秈 overflow

		if (ans.find('.') != string::npos)
		{
			if (count(res.begin(), res.begin() + 100, 9) > 50)
			{
				ans = addition(ans, "0.0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001");
				for (int i = ans.find('.') + 1; i < ans.length(); i++)
					ans[i] = '0';
			}
		}

		//for (int i = 0; i < res.size(); i++) cout << "[" << i << "] " << res[i] << endl;
	}



	c.setSign(!(sign == rhs.sign));
	c.setDigits(ans);
	c.setDotPlace(c.digits.find('.'));
	return c;

}

//  (1 / 3) * 3 = 1 -> 埃(process 柑耞)
BigInt BigInt::operator/(const BigInt rhs) const	// (digit - '0') / (rhs.digit - '0') -> A / B
{
	BigInt c;
	c.digits = "0";
	BigInt remain = *this; remain.sign = 0;
	BigInt divisor = rhs;  divisor.sign = 0;

	BigInt ten;
	ten.digits = "10";
	ten.sign = 0;
	ten.type = 0;
	ten.dotPlace = string::npos;

	c.setSign(!(sign == rhs.sign));	// タ璽计
	c.setType(type || rhs.type);

	if (rhs.compare("0") == 0)
	{
		c.digits = "default";		// 岿粇
		return c;
	}
	if (this->compare("0") == 0)
	{
		return c;
	}

	// if 12,345,678 / 234,567 = 52.6317768484 ; remain 148,194
	while (remain.compare(divisor.digits) > -1) // A > B
	{
		remain = remain - divisor;
		c.digits = addition(c.digits, "1");
	}

	if (c.type == 0)
		return c;
	c.digits += '.';		// now ansDigits = 52.
	int now;
	for (int i = 0; i < 100; i++)	//暗ansDigits计Τκ
	{
		now = 0;
		remain = remain * ten;
		//123.456/0.450
		while (remain.compare(divisor.digits) > -1)
		{
			remain = remain - divisor;
			now++;
		}
		c.digits += now + '0';
	}

	c.dotPlace = c.digits.find('.');

	return c;
}

BigInt BigInt::operator^(BigInt rhs) const
{
	BigInt one;
	one.digits = "1";
	one.sign = 0;
	one.type = 0;
	one.dotPlace = string::npos;

	BigInt ans = one;
	//b Τ琌 0.5 俱计

	while (rhs.compare("1") >= 0)
	{
		ans = ans * *this;
		rhs = rhs - one;
	}

	if (rhs.compare("0.5") == 0)
	{
		BigInt two = one + one;	two.type = 1; two.checkType();
		BigInt guess = *this / two;//guess will be equal to *this ^ 0.5
		BigInt r;
		BigInt temp;

		do {
			r = *this / guess;
			guess = (guess + r) / two;
			//cout << guess << endl;
			temp = r - guess;
			if (temp.sign == 1)temp.sign = 0;
		} while (temp.compare("0.00000000000000001") >= 0);

		ans = ans * guess;
	}

	return ans;
}

string addition(string A, string B)		// 常穦琌タ+タ (Τ计)
{
	int dot1 = A.find('.');
	int dot2 = B.find('.');
	int carry = 0;
	int len;
	int dot;
	int base = '0';

	if (dot1 == std::string::npos && dot2 == std::string::npos)		// 俱计 + 俱计
	{
		dot = dot1;
		// 干霍俱计
		while (A.length() < B.length())
			A = '0' + A;

		while (B.length() < A.length())
			B = '0' + B;

	}
	else if (dot1 == std::string::npos) //俱计 + 计
	{
		dot = (dot2 > A.length()) ? dot2 : A.length();
		// 干霍俱计
		while (dot2 < dot)
		{
			B = '0' + B;
			dot2++;
		}
		while (A.length() < dot)
			A = '0' + A;

		//干霍计
		A += '.';
		while (A.length() < B.length())
			A += '0';

	}
	else if (dot2 == std::string::npos) //计 + 俱计
	{
		dot = (dot1 > B.length()) ? dot1 : B.length();
		// 干霍俱计
		while (dot1 < dot)
		{
			A = '0' + A;
			dot1++;
		}
		while (B.length() < dot)
			B = '0' + B;

		//干霍计
		B += '.';
		while (B.length() < A.length())
			B += '0';
	}
	else 								// 计 + 计 eg: 123.3457 + 67.891
	{
		dot = max(dot1, dot2);
		//干霍俱计
		while (dot1 < dot2)
		{
			A = '0' + A;
			dot1++;
		}
		while (dot2 < dot1)
		{
			B = '0' + B;
			dot2++;
		}
		//干霍计
		while (A.length() < B.length())
			A += '0';

		while (B.length() < A.length())
			B += '0';
	}

	len = A.length();	//A.len == B.len┮ぃノゑ耕
	int temp;
	if (dot != string::npos)
	{
		for (int i = len - 1; i > dot; i--)//计场だ
		{
			temp = A[i] + B[i] - 2 * base + carry;
			carry = temp / 10;
			A[i] = temp % 10 + base;
		}
	}
	else
		dot = len;

	for (int i = dot - 1; i >= 0; i--)//俱计场だ
	{
		temp = A[i] + B[i] - 2 * base + carry;
		carry = temp / 10;
		A[i] = temp % 10 + base;
	}

	if (carry == 1) {
		A = '1' + A;
	}

	return A;
}

string subtraction(string A, string B)		// 常穦琌タ-タ (Τ计)
{
	int dot1 = A.find('.');
	int dot2 = B.find('.');
	int carry = 0;
	int len;
	int dot;
	int digit1 = 0, digit2 = 0;
	int base = '0';
	string ans = "";
	char ansSign;

	if (dot1 != std::string::npos && dot2 != std::string::npos)	//计 - 计
	{
		dot = max(dot1, dot2);
		//干霍俱计
		while (dot1 < dot2)
		{
			A = '0' + A;
			dot1++;
		}
		while (dot2 < dot1)
		{
			B = '0' + B;
			dot2++;
		}
		//干霍计
		while (A.length() < B.length())
			A += '0';
		while (B.length() < A.length())
			B += '0';
	}
	else if (dot1 == std::string::npos && dot2 == std::string::npos)		// 俱计 - 俱计
	{
		while (A.length() < B.length())
			A = '0' + A;
		while (B.length() < A.length())
			B = '0' + B;
	}
	else if (dot1 == std::string::npos)	// 俱计 - 计
	{
		dot = (dot2 > A.length()) ? dot2 : A.length();
		// 干霍俱计
		while (dot2 < dot)
		{
			B = '0' + B;
			dot2++;
		}
		while (A.length() < dot)
			A = '0' + A;

		//干霍计
		A += '.';
		while (A.length() < B.length())
			A += '0';
	}
	else								// 计 - 俱计
	{
		dot = (dot1 > B.length()) ? dot1 : B.length();
		// 干霍俱计
		while (dot1 < dot)
		{
			A = '0' + A;
			dot1++;
		}
		while (B.length() < dot)
			B = '0' + B;

		//干霍计
		B += '.';
		while (B.length() < A.length())
			B += '0';
	}

	//ゑ耕AB
	ansSign = '+';

	for (int i = 0; i < A.length(); i++)
	{
		if (A[i] > B[i])
			break;
		if (A[i] < B[i]) {
			ansSign = '-';
			A.swap(B);
			break;
		}
	}

	dot = max(dot1, dot2);
	// now A > B
	int len1 = A.length() - 1;
	int borrow = 0;
	ans = A;
	for (int i = len1; i > dot; i--) {
		ans[i] = ans[i] - B[i] - borrow + '0';

		if (ans[i] < '0') {
			borrow = 1;
			ans[i] = ans[i] + 10;
		}
		else {
			borrow = 0;
		}
	}
	for (int i = dot - 1; i >= 0; i--) {
		ans[i] = ans[i] - B[i] - borrow + '0';

		if (ans[i] < '0') {
			borrow = 1;
			ans[i] = ans[i] + 10;
		}
		else {
			borrow = 0;
		}
	}

	while (ans[0] == '0')
		ans.erase(0, 1);

	if (ans.length() == 0 || ans[0] == '.')
		ans = '0' + ans;

	if (ansSign == '-') {
		ans = '-' + ans;
	}
	return ans;
}

void BigInt::operator=(const BigInt& rhs)
{
	type = rhs.type;
	//nameぃノэ
	digits = rhs.digits;
	dotPlace = rhs.dotPlace;
	sign = rhs.sign;
}

int BigInt::compare(string B) const
{
	//肚: -1:<  0:==  1:>

	//if sign is different
	if (B[0] == '-')
	{
		if (sign == 0)
			return 1;
		B.erase(0, 1);//璽腹獽耞
	}
	else if (sign == 1)
		return -1;

	string A = digits;
	int dot1 = A.find('.'),
		dot2 = B.find('.'),
		dot = max(dot1, dot2);

	if (dot1 == string::npos)
	{
		dot1 = A.length();
		A += ".0";
	}
	if (dot2 == string::npos)
	{
		dot2 = B.length();
		B += ".0";
	}
	//干霍俱计
	while (dot1 < dot2)
	{
		A = '0' + A;
		dot1++;
	}
	while (dot2 < dot1)
	{
		B = '0' + B;
		dot2++;
	}
	//干霍计
	while (A.length() < B.length())
		A += '0';

	while (B.length() < A.length())
		B += '0';

	//start compare
	for (int i = 0; i < A.length(); i++)
	{
		if (A[i] < B[i])
			return -1;
		else if (A[i] > B[i])
			return 1;
	}
	return 0;
}

ostream& operator<<(ostream& strm, const BigInt& now)
{
	if (now.sign)
		strm << '-';
	strm << now.digits;
	return strm;
}