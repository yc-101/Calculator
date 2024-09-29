#pragma once
#include "BigInt.h"
using namespace std;
BigInt operation(BigInt a, BigInt b, string op)
{
	if (op == "+")
		return a + b;

	else if (op == "-")
		return a - b;

	else if (op == "*")
		return a * b;

	else if (op == "/")
		return a / b;


	cout << "operation error\n";
	return a;
}


int getPriority(char cmd)
{
	switch (cmd)
	{
	case ','://Power(a,b)
		return 1;
	case '+'://**�[�� & ���t�� ���Ϥ�?
	case '-':
		return 2;
	case '*':
	case '/':
		return 3;
	case '^':
		return 4;
	case '!':
		return 5;
	case '(':
	case ')':
		return 6;
	default:
		return 0;
	}
}


BigInt process(string s)
{
	string infix;
	//�M���Ů�
	//infix.erase(std::remove(infix.begin(), infix.end(), ' '), infix.end());//remove space ' '
	for (int i = 0; i < s.length(); i++)
		if (s[i] != ' ')
			infix += s[i];

	//-------------------------------------------
	// ���Ԧ� -> ��Ǧ� <Infix to Postfix>
	//-------------------------------------------
	BigInt nowVar;//an number to save into stack
	nowVar.sign = 0;
	vector<BigInt> postfix, stack;
	BigInt now;//an operation to save into stack
	now.sign = 0;
	now.type = 2;
	bool isNegative = false;	//�ϧO�t��&���
	bool doPower = false;
	bool check = false;

	for (int i = 0; i < infix.length(); i++)
	{
		switch (infix[i])
		{
		case'(':
			now.digits = "(";
			if (isNegative)
			{
				now.sign = 1;
				isNegative = 0;
			}
			else now.sign = 0;
			stack.push_back(now);
			break;

		case')': //�@�������ӬA���]��
			while (stack.size() > 0)
			{
				if (stack.back().digits == "(")
				{
					stack.pop_back();
					break;
				}
				else
				{
					postfix.push_back(stack.back());
					stack.pop_back();
				}
			}
			break;

		default:
			int priority = getPriority(infix[i]);
			if (priority > 0)	//���O�Ʀr
			{
				if ((infix[i] == '+' || infix[i] == '-') && (i == 0 || getPriority(infix[i - 1]) != 0)) //�e�@�Ӥ��O�Ʀr or �o�b���l�̫e���A�o�N�O�t��
				{
					if (i > 2 && infix[i - 1] != '(' && infix[i - 2] != '(') {
						break;
					}

					if (infix[i] == '-')
						if (isNegative)
							isNegative = 0;
						else
							isNegative = 1;
					break;	//���t�����|�bstack�̭��A�P�_stack�ɤ~���|�V�c�t��&�
				}

				while (stack.size() > 0)
				{
					if (stack.back().digits == "(")
						break;

					if (priority > getPriority(stack.back().digits[0]))
						break;

					if (priority == 4)//�����O�ѥk�ܥ��B��(2^3^4 == 2^(3^4))
						break;

					postfix.push_back(stack.back());
					stack.pop_back();
				}
				now.type = 2;
				now.digits.clear();
				now.digits = infix[i];
				stack.push_back(now);
			}
			else
			{
				if (i + 1 < infix.length() && getPriority(infix[i + 1]) == 0) //�U�@��]�O�P�ӼƦr or �^��
					nowVar.digits.push_back(infix[i]);

				else { //�U�@�椣�O�Ʀr or �^��
					nowVar.digits.push_back(infix[i]);
					if (nowVar.digits[0] > '9' || nowVar.digits[0] < '0')//�O�@���ܼƦW�� or Power
					{
						if (nowVar.digits[0] == 'P' && nowVar.digits[1] == 'o' && nowVar.digits[2] == 'w' && nowVar.digits[3] == 'e' && nowVar.digits[4] == 'r')
						{
							//doPower = true;
							nowVar.digits.clear();

							break;
						}
						for (int i = 0; i < BigInt::All.size(); i++)
						{
							if (BigInt::All[i].name == nowVar.digits)
							{
								nowVar = BigInt::All[i];
								break;
							}
						}
					}
					else
					{
						nowVar.dotPlace = nowVar.digits.find('.');
						if (nowVar.dotPlace == string::npos) //�O���
							nowVar.type = 0;
						else
							nowVar.type = 1;

						nowVar.checkType();
					}
					if (check) break;

					if (isNegative)
					{
						if (nowVar.sign)
							nowVar.sign = 0;
						else
							nowVar.sign = 1;

						isNegative = false;
					}
					postfix.push_back(nowVar);
					nowVar.digits.clear();
					nowVar.sign = 0;
				}
			}
			break;
		}
	}

	while (stack.size() > 0)
	{
		postfix.push_back(stack.back());
		stack.pop_back();
	}

	cout << "\n-------------------final  postfix-------------------\n\n";
	for (int i = 0; i < postfix.size(); i++)
		cout << (postfix[i].sign ? '-' : ' ') << postfix[i].digits << ",\n";
	cout << "\n----------------------------------------------------\n";


	//cout << "\n-------------------- [�B��i��] --------------------\n";
	//-------------------------------------------
	// ���Ǧ� <Evaluate Postfix>
	//-------------------------------------------
	BigInt ERROR;
	ERROR.digits = "default";
	ERROR.sign = 0;

	for (int i = 0; i < postfix.size(); i++)
	{
		if ((postfix[i].digits == "+") || (postfix[i].digits == "-") || (postfix[i].digits == "*") || (postfix[i].digits == "/") || (postfix[i].digits == "," || (postfix[i].digits == "^")))
		{
			//�B��
			BigInt a, b;
			if (getPriority(stack.back().digits[0])) //�Ya,b ���O�Ʀr�A�N��X���~
				return ERROR;
			else
			{
				b = stack.back();
				stack.pop_back();
			}

			if (getPriority(stack.back().digits[0]))
				return ERROR;
			else
			{
				a = stack.back();
				stack.pop_back();
			}
			

			if (postfix[i].digits == "+")
				stack.push_back(a + b);

			else if (postfix[i].digits == "-")
				stack.push_back(a - b);

			else if (postfix[i].digits == "*")
				stack.push_back(a * b);

			else if (postfix[i].digits == "/")
				stack.push_back(a / b);

			else if ((postfix[i].digits == "^") || (postfix[i].digits == ","))
				stack.push_back(a ^ b);

			else cout << "operation error\n";

			if (postfix[i].sign == 1)
			{
				if (stack.back().sign == 1)
					stack.back().sign = 0;
				else stack.back().sign = 1;
			}

			if (stack.back().digits == "default")
			{
				stack.back().sign = 0;
				return stack.back();
			}
			if (stack.back().digits == "0")
			{
				stack.back().sign = 0;
			}

		}
		else if (postfix[i].digits == "!")
		{
			BigInt a = stack.back();
			stack.pop_back();
			if (a.type != 0 || a.sign != 0) {
				for (int i = a.digits.find('.') + 1; i < a.digits.length(); i++)
				{
					if (a.digits[i] != '0')
					{
						cout << "Illegal : �����B�⶷���Υ����\n�Э��s��J : ";
						a.digits = "default";
						a.sign = 0;
						return a;
					}
				}
			}

			BigInt one;
			one.digits = "1"; one.type = 0; one.sign = 0;
			if (a.compare("0") == 0) // 0!
				stack.push_back(one);
			else
			{
				BigInt times = a - one;
				while (times.compare("1") == 1) //a > 1
				{
					a = a * times;
					times = times - one;
				}
				stack.push_back(a);
			}
		}
		else
		{
			stack.push_back(postfix[i]);
		}
	}

	if (stack.back().getDigits().find('.') == string::npos) //�O���
		stack.back().setType(0);
	else
		stack.back().setType(1);

	stack.back().checkType();
	return stack.back();
}

void printAllVar()
{
	cout << "--------------------�ثe�Ҧ��ܼ�--------------------\n";
	for (auto now : BigInt::All)
	{
		cout << now.getName() << " = " << now << endl;
	}
	cout << "----------------------------------------------------\n";
}