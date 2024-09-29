#include "BigInt.h"
#include "NumberObject.h"
#include "main.h"

#include <sstream>	//istringstream https://www.twblogs.net/a/5b8a17392b71775d1ce55f47
#include<Windows.h>
using namespace std;


int main()
{
	string line;
	istringstream istr;
	string cmd;
	BigInt temp;
	string to_process;
	/*
		做一個vector紀錄左右括弧的位置，
		每次讀到左括弧就push_back到[i][0]
		直到讀到右括弧，開始i-- 並push_back[i][1]
	*/
	/*
	cout << process("1.5 + 3 * ( -(-5) )") << endl;
	temp.setDigits(process("15 + 27.4").getDigits());
	BigInt::All.push_back(temp);
	*/
	cout << "--------------------------------------------\n"
		<< "| functions:                               |\n"
		<< "|    · a function with + - * / ( )         |\n"
		<< "|    · Power(... , ...) or directly use ^  |\n"
		<< "|                                          |\n"
		<< "| to set variables:                        |\n"
		<< "|    · Set Integer [VAR_NAME] [VAR]        |\n"
		<< "|    · Set Decimal [VAR_NAME] [VAR]        |\n"
		<< "|                                          |\n"
		<< "| to test Integer & Decimal class:         |\n"
		<< "|    · -T  (cin, cout)                     |\n"
		<< "|    · -U  (Integer = \"     \")             |\n"
		<< "--------------------------------------------\n\n";
	printAllVar();
	cout << "\n輸入運算式or設變數 : \n";

	while (getline(std::cin, line))
	{
		if (line.size() == 0)
			continue;

		istr.clear();
		istr.str(line);
		istr >> cmd;

		if (cmd == "Set")
		{
			int i = 12; //nameStart

			istr >> cmd;
			if (cmd == "Integer")
				temp.setType(0);

			else if (cmd == "Decimal")
				temp.setType(1);

			else
			{
				cout << "Illegal : 未輸入正確 Integer or Decimal\n請重新輸入 : ";
				continue;
			}

			//read name (until '=')
			int equalPlace = line.find('=');
			if (equalPlace == string::npos)
			{
				cout << "Illegal : 未輸入等號\n請重新輸入 : ";
				continue;
			}

			string name;
			name.assign(line, 12, equalPlace - 12);
			temp.setName(name);

			//set digits (after '=')
			to_process.clear();
			to_process.assign(line, equalPlace + 1, line.length());

			//cout << "to_process: " << to_process << endl;
			if (temp.getType() == 0)
			{
				temp = process(to_process);
				temp.setType(0);
			}
			else
			{
				temp = process(to_process);
				temp.setType(1);
			}
			if (temp.getDigits() == "default")
			{
				cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
				break;
			}
			temp.checkType();

			bool check = 0;
			for (int i = 0; i < BigInt::All.size(); i++)
			{
				if (BigInt::All[i].getName() == temp.getName())
				{
					cout << temp.getName() << " already exist, change it to the new one.\n";
					BigInt::All[i] = temp;
					check = 1;
					break;
				}
			}
			if (!check)
			{
				cout << "\nSet type: " << (temp.getType() == 0 ? "Integer" : "Decimal")
					<< "\nname: " << temp.getName()
					<< "\ndigits = " << temp << endl;
				//cout << "\n-------------------- [運算結束] --------------------\n\n";
				BigInt::All.push_back(temp);
			}
		}

		else if (cmd == "-T")
		{
			Integer i;
			Decimal d;
			cout << "cin >> Integer i : ";
			cin >> i;
			cout << "cin >> Decimal d : ";
			cin >> d;

			temp = process(i.getDigits()); i = temp;
			if (temp.getDigits() == "default")
			{
				cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
				break;
			}

			temp = process(d.getDigits()); d = temp;
			if (temp.getDigits() == "default")
			{
				cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
				break;
			}

			cout << "i = " << i << endl
				<< "d = " << d << endl
				<< "i + d = " << i + d << endl
				<< "d + i = " << d + i << endl
				<< "i - d = " << i - d << endl
				<< "d - i = " << d - i << endl
				<< "i * d = " << i * d << endl
				<< "d * i = " << d * i << endl
				<< "i / d = " << i / d << endl
				<< "d / i = " << d / i << endl;

			vector<BigInt*> nums;
			nums.push_back(&i);
			nums.push_back(&d);
			cout << "--------繼承:--------\n";
			for (const auto& num : nums)
				cout << *num << endl;
			cout << "---------------------\n";
		}
		else if (cmd == "-U")
		{
			Integer i = "12345";
			Decimal d = "0.3 * 3";
			temp = process(i.getDigits()); i = temp;
			if (temp.getDigits() == "default")
			{
				cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
				break;
			}
			temp = process(d.getDigits()); d = temp;
			if (temp.getDigits() == "default")
			{
				cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
				break;
			}
			cout << "i = " << i << endl
				<< "d = " << d << endl
				<< "i + d = " << i + d << endl
				<< "d + i = " << d + i << endl
				<< "i - d = " << i - d << endl
				<< "d - i = " << d - i << endl
				<< "i * d = " << i * d << endl
				<< "d * i = " << d * i << endl
				<< "i / d = " << i / d << endl
				<< "d / i = " << d / i << endl;

			vector<BigInt*> nums;
			nums.push_back(&i);
			nums.push_back(&d);
			cout << "--------繼承:--------\n";
			for (const auto& num : nums)
				cout << *num << endl;
			cout << "---------------------\n";
		}


		else if (cmd != "Set" && line[0] != '-' && !isdigit(line[0]) && line[0] != '(' &&
			(cmd[0] != 'P' || cmd[1] != 'o' || cmd[2] != 'w' || cmd[3] != 'e' || cmd[4] != 'r')) {

			bool chk = 0;
			for (int i = 0; i < BigInt::All.size(); i++) {
				if (line.find(BigInt::All[i].getName()) != string::npos) {
					to_process.clear();
					to_process = line;
					//cout << "to_process: " << to_process << endl;
					temp = process(to_process);
					//cout << "\n\n-------------------- [運算結束] --------------------\n";
					if (temp.getDigits() == "default")
					{
						cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
						chk = 0;
					}
					else
					{
						cout << endl << "Ans : " << temp << endl << endl;
						chk = 1;
					}
					break;
				}
			}
			if (chk == 0) {
				cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
				continue;
			}
		}

		else
		{
			to_process.clear();
			to_process = line;
			//cout << "to_process: " << to_process << endl;
			temp = process(to_process);
			if (temp.getDigits() == "default")
			{
				cout << "Illegal : 未輸入正確運算式或變數指令\n請重新輸入 : ";
				continue;
			}
			//cout << "\n\n-------------------- [運算結束] --------------------\n";
			cout << endl << "Ans : " << temp << endl << endl;
		}
		cout << "[enter to continue]\n";
		getline(std::cin, line);

		system("cls");

		cout << "--------------------------------------------\n"
			<< "| functions:                               |\n"
			<< "|    · a function with + - * / ( )         |\n"
			<< "|    · Power(... , ...) or directly use ^  |\n"
			<< "|                                          |\n"
			<< "| to set variables:                        |\n"
			<< "|    · Set Integer [VAR_NAME] [VAR]        |\n"
			<< "|    · Set Decimal [VAR_NAME] [VAR]        |\n"
			<< "|                                          |\n"
			<< "| to test Integer & Decimal class:         |\n"
			<< "|    · -T  (cin, cout)                     |\n"
			<< "|    · -U  (Integer = \"     \")             |\n"
			<< "--------------------------------------------\n\n";
		printAllVar();
		cout << "\n輸入運算式or設變數 : \n";
	}

	//process("1.5 + 3 * (6 + 7)"); // 1.5 3 6 7 + * +
	//cout << process("1.5 + 3 * (-(-5))");
}

//=======沒過的測資=======

//6-(-(-7))

//========過的測資========
//3-(2-1)
//1.5+3*(6-(-7))
//-3+3
//1/3.0*3   
//(1/3.0*6)!   
//-(-5+7)  
//-(5+7)  
//6/2^2
//4/5
//0.0/0 =0
//-5/0
//-3-(-(-(-3)))	
//-3-3+3-(-3)   
//-5/5   
//-5/-5   
//5/(-5)    
//-0.6/1