#pragma once
#include "largeinterger.h"
#include <iostream>


#define jump_op while (getchar() != '\n');


using namespace std;

void printvector(vector<unsigned char> a)
{
	vector<unsigned char>::iterator ptra;
	for (ptra=a.begin(); ptra!=a.end(); ptra++)
		cout << *ptra;
	cout << endl;
}



void main() {
	//local variable
	char op,temp,mark;
	vector<unsigned char> temp2;
	Interger number1;
	Interger number2;
	cout << "input the first number" << endl;
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
			if (number1.number[0]==0x00)  //if the number is available
			{
				cout << "error" << endl;
				jump_op
				jump_op
				cout << "new input first number:" << endl;
				continue;
			}

			//input the second number
			cout << "input the next number" << endl;
			temp = getchar();
			if ((temp > '9'&&temp < '0') && temp != '+' && temp != '-')
			{
				cout << "error" << endl;
				jump_op
				jump_op
				cout << "new input first number:" << endl;
				continue;
			}
			number2 = Interger(temp);
			if (number2.number[0] == 0x00)//if the number is available
			{
				cout << "error" << endl;
				jump_op
				cout << "new input first number:" << endl;
				continue;
			}

			/*
			test the input of the number
			cout << number1.number << endl << number1.length << endl << number1.signal << endl;
			cout << number2.number << endl << number2.length << endl << number2.signal << endl;
			*/

			//input the operation
			cout << "input the operation" << endl;
			cin >> op;
			Interger* answer=new Interger;
			answer->number.clear();
			switch (op)
			{
			case '+':
				if (number1.signal == number2.signal)
				{
					cout << (number1.signal ? "" : "-");
					number1.add(&number2, answer);
					printvector(answer->number);
					delete answer;
					cout << "new input first number:" << endl;
				}
				else if (number1.signal == false)
				{
					number2.sub(&number1, answer);
					cout << (answer->signal ? "" : "-");
					printvector(answer->number);
					delete answer;
					cout << "new input first number:" << endl;
				}
				else
				{
					number1.sub(&number2, answer);
					cout << (answer->signal ? "" : "-");
					printvector(answer->number);
					delete answer;
					cout << "new input first number:" << endl;
				}
				break;
			case '-':
				if (number1.signal != number2.signal)
				{
					cout << (number1.signal ? "" : "-");
					number1.add(&number2, answer);
					printvector(answer->number);
					delete answer;
					cout << "new input first number:" << endl;
				}
				else if (number1.signal == false)
				{
					number2.sub(&number1, answer);
					cout << (answer->signal ? "" : "-");
					printvector(answer->number);
					delete answer;
					cout << "new input first number:" << endl;
				}
				else
				{
					number1.sub(&number2, answer);
					cout << (answer->signal ? "" : "-");
					printvector(answer->number);
					delete answer;
					cout << "new input first number:" << endl;
				}
				break;
			case '*':
				cout << ((number1.signal^number2.signal) ? "-" : "");
				number1.length <= number2.length ? number2.time(&number1, answer) : number1.time(&number2, answer);
				printvector(answer->number );
				delete answer;
				cout << "new input first number:" << endl;
				break;
			case '/':
				if (number2.number[0] == '0')
				{
					cout << "divide 0" << endl;
					break;
				}
				mark = number1.signal^number2.signal ?  '-':0x0;
				cout << "the result is:" << mark;
				number1.divide(&number2, answer);
				printvector(answer->number);
				delete answer;
				cout << "the remainder is :" << mark;
				printvector(number1.number);
				cout << "new input first number:" << endl;
				break;
			default:
				cout << "error" << endl;
				cout << "new input first number:" << endl;
				break;
			}
		}
		else
		{
			cout << "error" << endl;
			jump_op
			jump_op
			jump_op
			cout << "new input first number:" << endl;
			continue;
		}
	}
	
	return;
}