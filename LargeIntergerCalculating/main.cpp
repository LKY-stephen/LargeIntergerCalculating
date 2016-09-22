#pragma once
#include "largeinterger.h"
#include <iostream>

using namespace std;

void main() {
	//local variable
	char op;

	//input first integer
	cout << "input first number:"<<endl;
	Interger number1= Interger();
	if (number1.number == "")  //if the number is available
	{
		cout << "error" << endl;
		return;
	}

	//input the second number
	cout << "input second number:"<<endl;
	Interger number2 = Interger();
	if (number2.number == "")//if the number is available
	{
		cout << "error" << endl;
		return;
	}

	/*
	test the input of the number
	cout << number1.number << endl << number1.length << endl << number1.signal << endl;
	cout << number2.number << endl << number2.length << endl << number2.signal << endl;
	*/

	//input the operation
	cout << "input opera:" << endl;
	cin >> op;
	switch (op)
	{
	case '+':
		if (number1.signal == number2.signal)
		{
			cout << number1.add(number2) << endl;
		}
		else if(number1.signal==false)
		{
			cout << number2.sub(number1)<<endl;
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
		cout << "error" << endl;
		break;
	}
	
	return;
}