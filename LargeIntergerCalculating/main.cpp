#pragma once
#include "largeinterger.h"
#include <iostream>

#define jump_op while (getchar() != '\n');


using namespace std;

void main() {
	//local variable
	char op;
	char temp;
	string temp2;
	Interger number1;
	Interger number2;
	while ((temp=getchar())!= EOF)
	{
		if (temp == '\n')
		{
			continue;
		}
		if ((temp <= '9'&&temp >= '0') || temp == '+' || temp == '-')
		{

			 number1 = Interger(temp);
			//input first integer
			if (number1.number == "")  //if the number is available
			{
				cout << "error" << endl;
				jump_op
				jump_op
				cout << "new input:" << endl;
				continue;
			}

			//input the second number
			temp = getchar();
			if ((temp > '9'&&temp < '0') && temp != '+' && temp != '-')
			{
				cout << "error" << endl;
				jump_op
				jump_op
				cout << "new input:" << endl;
				continue;
			}
			number2 = Interger(temp);
			if (number2.number == "")//if the number is available
			{
				cout << "error" << endl;
				jump_op
				cout << "new input:" << endl;
				continue;
			}

			/*
			test the input of the number
			cout << number1.number << endl << number1.length << endl << number1.signal << endl;
			cout << number2.number << endl << number2.length << endl << number2.signal << endl;
			*/

			//input the operation
			cin >> op;
			switch (op)
			{
			case '+':
				if (number1.signal == number2.signal)
				{
					cout << number1.add(number2) << endl;
					cout << "new input:" << endl;
				}
				else if (number1.signal == false)
				{
					cout << number2.sub(number1) << endl;
					cout << "new input:" << endl;
				}
				else
				{
					cout << number1.sub(number2) << endl;
					cout << "new input:" << endl;
				}
				break;
			case '-':
				if (number1.signal != number2.signal)
				{
					cout << number1.add(number2) << endl;
					cout << "new input:" << endl;
				}
				else if (number1.signal == false)
				{
					cout << number2.sub(number1) << endl;
					cout << "new input:" << endl;
				}
				else
				{
					cout << number1.sub(number2) << endl;
					cout << "new input:" << endl;
				}
				break;
			case '*':
				if (number1.length <= number2.length)
				{
					cout << number2.time(number1) << endl;

				}
				else
				{
					cout << number1.time(number2) << endl;
				}
				cout << "new input:" << endl;
				break;
			case '/':
				cout << number1.divide(number2) << endl;
				cout << "new input:" << endl;
				break;
			default:
				cout << "error" << endl;
				cout << "new input:" << endl;
				break;
			}
		}
		else
		{
			cout << "error" << endl;
			jump_op
			jump_op
			jump_op
			cout << "new input:" << endl;
			continue;
		}
	}
	
	return;
}