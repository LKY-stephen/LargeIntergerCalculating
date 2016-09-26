#pragma once
#include "largeinterger.h"
#include<iostream>
using namespace std;
Interger::Interger(char head)
{
	char  temp;
	if (head == '-')
	{
		number = "";
		signal = false;
	}
	else if (head >= '0'&&head <= '9')
	{
		number = head;
		signal = true;
	}
	else
	{
		number = "";
		signal = true;
	}
	
	while ((temp = getchar()) != '\n')
	{
		if (temp > '9' || temp < '0')
		{
			number = "";
			break;
		}
		else if (temp == '0')
		{
			if (number == "0")
			{
				continue;
			}
			else
			{
				number+=temp;
			}
		}
		else
		{
			if (number == "0")
			{
				number = temp;
			}
			number += temp;
		}
	}
	length=number.size();
}

Interger::Interger()
{
	__nop;
}

Interger::Interger(string num)
{
	number = num;
	length = number.size();
	signal = true;

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
	Interger tempstr[10];
	for (int i = 0; i < 10; i++)
	{
		tempstr[i] = Interger("");
	}
	Interger answer=Interger("0");
	int opr = 0;

	for (int i = 0; i < number2.length; i++)
	{
		//calculate every possability
		opr = number2.number[i] - '0';
		if (tempstr[opr].number == "")
		{
			tempstr[opr]= Interger(time(opr));
		}

		//add the result
		answer.time(10);
		answer=Interger(answer.add(tempstr[opr]));
	}
	return (signal^number2.signal?"-":"")+answer.number;
}

string Interger::time(int y)
{
	int carryb=0,leftb, opr, tempb=0;
	char temp;
	string answer="";
	if (y == 0)
	{
		return "0";
	}
	else if (y == 1)
	{
		return number;
	}
	else if (y == 10)
	{
		if (number != "0")
		{
			number += '0';
			length++;
		}
		return number;
	}
	for (int i = length-1; i >=0; i--)
	{
		opr = number[i] - '0';
		tempb = opr*y+carryb;
		leftb = tempb % 10;
		carryb = (tempb - leftb) / 10;
		temp = leftb + '0';
		answer = temp + answer;
	}
	return answer;
}


string Interger::divide(Interger number2)
{
	return string();
}
