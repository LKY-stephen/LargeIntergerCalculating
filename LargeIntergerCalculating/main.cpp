#pragma once
#include "largeinterger.h"
#include <iostream>

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
				cin >> temp2;
				cin >> temp;
				continue;
			}

			//input the second number
			temp =0x0;
			number2 = Interger(temp);
			if (number2.number == "")//if the number is available
			{
				cin >> temp;
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
				}
				else if (number1.signal == false)
				{
					cout << number2.sub(number1) << endl;
				}
				else
				{
					cout << number1.sub(number2) << endl;
				}
				break;
			case '-':
				if (number1.signal != number2.signal)
				{
					cout << number1.add(number2) << endl;
				}
				else if (number1.signal == false)
				{
					cout << number2.sub(number1) << endl;
				}
				else
				{
					cout << number1.sub(number2) << endl;
				}
				break;
			case '*':
				cout << number1.time(number2) << endl;
				break;
			case '/':
				cout << number1.divide(number2) << endl;
				break;
			default:
				break;
			}
		}
		else
		{
			cin >> temp2;
			cin >> temp2;
			cin >> temp;
			continue;
		}
	}
	
	return;
}