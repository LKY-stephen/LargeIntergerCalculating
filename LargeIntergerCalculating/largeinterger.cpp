#pragma once
#include "largeinterger.h"
#include<iostream>
using namespace std;
Interger::Interger()
{
	cin >> number;
	if (number[0] == '-'){
		number = number.substr(1);
		signal = false;
	}
	else
	{
		signal = true;
	}
	length = number.size();
	for(int i=0;i<length;i++){
		if (number[i]<'0' || number[i]>'9') {
			number = "";
			break;
		}
	}
}

string Interger::add(Interger number2)
{
	return string();
}

string Interger::sub(Interger number2)
{
	return string();
}

string Interger::time(Interger number2)
{
	return string();
}

string Interger::divide(Interger number2)
{
	return string();
}
