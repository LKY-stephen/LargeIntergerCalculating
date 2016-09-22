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
	char carry=0x0;
	char temp=0;
	string answer = "";
	int iterator1 = length - 1;
	int iterator2 = number2.length - 1;
	
	//add the small number
	while (iterator1 >= 0 && iterator2 >= 0)
	{
		temp = carry+number[iterator1] + number2.number[iterator2]-'0';
		if (temp > '9')
		{
			carry = 0x1;
			temp -= 10;
		}
		else
		{
			carry = 0x0;
		}
		answer = temp + answer;
		iterator1--;
		iterator2--;
	}
	//add the large part
	if (carry == 0x0)
	{   //no carrybit
	    if (iterator1 >= 0)
		{
			answer = number.substr(0, iterator1 + 1) + answer;
		}
		else if (iterator2 >= 0)
		{
			answer = number2.number.substr(0, iterator2 + 1) + answer;
		}
	}
	else
	{   //carry bit
		if (iterator1 >= 0)
		{
			int i;
			for (i = iterator1; i >= 0; i--)
			{
				if (number[i] != '9')
				{
					number[i]++;
					break;//break for
				}//endif
			}
			for (int j = i+1; j <= iterator1; j++)
			{
				number[j] = '0';
			}
			if (i >= 0)
			{
				answer = number.substr(0, iterator1 + 1) + answer;
			}
			else
			{
				answer='1'+ number.substr(0, iterator1 + 1) + answer;
			}
			
		}//endif
		else if (iterator2 >= 0)
		{
			int i;
			for (i = iterator2; i >= 0; i--)
			{
				if (number2.number[i] != '9')
				{
					number2.number[i]++;
					break;//break for
				}//endif
			}
			for (int j = i + 1; j <= iterator2; j++)
			{
				number2.number[j] = '0';
			}
			if (i >= 0)
			{
				answer = number2.number.substr(0, iterator2 + 1) + answer;
			}
			else
			{
				answer = '1' + number2.number.substr(0, iterator2 + 1) + answer;
			}

		}//end elseif
		else
		{
			answer = '1' + answer;
		}//end else
	}
	if (signal == false)
	{
		return '-' + answer;
	}
	else
	{
		return answer;
	}
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
