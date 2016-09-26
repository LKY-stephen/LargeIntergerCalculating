#pragma once
#include "largeinterger.h"
#include<iostream>
using namespace std;
Interger::Interger(char head)
{
	cin >> number;
	if (head != 0x0)
	{
		number = head+number;
	}
	if (number[0] == '-'){
		number = number.substr(1);
		signal = false;
	}
	else if (number[0] == '+') {
		number = number.substr(1);
		signal = true;
	}
	else
	{
		signal = true;
	}
	//clear 0
	for (int i = 0; i < number.size(); i++)
	{
		if (number[i] != '0')
		{
			number = number.substr(i, number.size() - i);
			break;
		}
	}
	length = number.size();
	for(int i=0;i<length;i++){
		if (number[i]<'0' || number[i]>'9') {
			number = "";
			break;
		}
	}
}

Interger::Interger()
{
	__nop;
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
		{//number1 has left
			int i;
			for (i = iterator1; i >= 0; i--)
			{
				if (number[i] != '9')
				{
					number[i]++;
					break;//break for
				}
				number[i] = '0';
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
				}
				number[i] = '0';
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
	bool answersignal;
	string answer = "";
	char temp = '0';
	int iterator1;
	int iterator2;

	//decide the sgn
	if (length > number2.length)
	{
		answersignal = true;
	}
	else if (length < number2.length)
	{
		answersignal = false;
	}
	else
	{
		int i=0;
		for (i = 0; number[i] == number2.number[i]&&i<length; i++);
		if (i == length)
		{
			return "0";
		}
		else
		{
			answersignal = number[i] > number2.number[i] ? true : false;
		}
	}


	if (answersignal)
	{
		iterator2 = number2.length-1;
		iterator1 = length-1;
		while (iterator2 >= 0)
		{
			if (number[iterator1] < number2.number[iterator2])
			{
				for (int j = iterator1-1; j >= 0; j--)
				{
					if (number[j] > '0')
					{
						number[j]--;
						break;//break for
					}
					number[j] = '9';
				}
				temp= (number[iterator1] - number2.number[iterator2] + 10)+'0';
			}//endif
			else
			{
				temp= (number[iterator1] -number2.number[iterator2])+'0';
			}
			answer = temp + answer;
			iterator1--;
			iterator2--;
		}//endwhile
		if (iterator1 >= 0)
		{
			answer = number.substr(0, iterator1 + 1) + answer;
		}
	}//end answersignal==true
	else
	{
		iterator1 = number2.length - 1;
		iterator2 = length - 1;
		while (iterator2 >= 0)
		{
			if (number2.number[iterator1] < number[iterator2])
			{
				for (int j = iterator1-1; j >= 0; j--)
				{
					if (number2.number[j] > '0')
					{
						number2.number[j]--;
						break;//break for
					}
					number2.number[j] = '9';
				}
				temp = (number2.number[iterator1] - number[iterator2] + 10 )+ '0';
			}//endif
			else
			{
				temp = (number2.number[iterator1] - number[iterator2] )+ '0';
			}
			answer = temp + answer;
			iterator1--;
			iterator2--;
		}//endwhile
		if (iterator1 >= 0)
		{
			answer = number2.number.substr(0, iterator1 + 1) + answer;
		}
	}
	for (int i = 0; i < answer.size(); i++)
	{
		if (answer[i] != '0')
		{
			answer = answer.substr(i, answer.size() - i);
			break;
		}
	}
	return (answersignal?"":"-")+answer;
}

string Interger::time(Interger number2)
{
	string tempanswer[9];

	return string();
}

string Interger::divide(Interger number2)
{
	return string();
}
