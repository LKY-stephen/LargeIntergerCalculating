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
	return;
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
	for (unsigned int i = 0; i < answer.size(); i++)
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
		tempstr[i].number = "0";
		tempstr[i].length = 1;
		tempstr[i].signal = true;
	}
	Interger answer;
	answer.number = "0";
	answer.length = 1;
	answer.signal = true;
	int opr = 0;

	for (int i = 0; i < number2.length; i++)
	{
		//calculate every possability
		opr = number2.number[i] - '0';
		if (opr == 0)
		{
			answer.number += '0';
			answer.length++;
			continue;
		}
		else if (tempstr[opr].number == "0")
		{
			tempstr[opr].number= time(opr);
			tempstr[opr].length = tempstr[opr].number.size();
		}
		//add the result
		if (answer.number != "0")
		{
			answer.number += '0';
			answer.length++;
		}
		answer.number=answer.add(tempstr[opr]);
		answer.length = answer.number.size();
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
	for (int i = length-1; i >=0; i--)
	{
		opr = number[i] - '0';
		tempb = opr*y+carryb;
		leftb = tempb % 10;
		carryb = (tempb - leftb) / 10;
		temp = leftb + '0';
		answer = temp + answer;
	}
	if (carryb)
	{
		temp = carryb + '0';
		answer = temp + answer;
	}
	return answer;
}


string Interger::divide(Interger number2)
{
	
	signal = (signal^number2.signal?false:true);
	Interger result;
	result.number = "";
	result.length = 0;
	result.signal = signal;
	Interger tempstr[11];
	int i, j,k,opr,loss,carry=0;
	char mark= signal ? 0x0 : '-';
	
	


	for ( i = 0; i < 11; i++)
	{
		tempstr[i].number = "0";
		tempstr[i].length = 1;
		tempstr[i].signal = true;
	}
	if (number2.length > length)
	{
		return "0";
	}
	while ( length >= number2.length)
	{
		loss = 0;
		for ( j = 0; j < number2.length&&number[j] == number2.number[j]; j++);
		if (j == number2.length)// if all the number is equal to number2
		{
			number = number.substr(number2.length, length - number2.length);
			length -= number2.length;
			i += number2.length - 1;
			result.number += "1";
			result.length += number2.length;
			loss = number2.length - 1;
		}
		else 
		{
			if ((number[0] < number2.number[0]) || (j > 0 && number[j] < number2.number[j]))
			{
				if (result.number != ""&&carry==0)
				{
					result.number += "0";
					result.length++;
				}
				opr = ((number[0] - '0') * 10 + (number[1] - '0')) / (number2.number[0] - '0' + 1);
				carry = 1;
			}
			else
			{
				opr = (number[0] - '0') / (number2.number[1] - '0' + 1);
			}
			
			//determin the value of result
			
			if (tempstr[opr].number == "0")
			{
				tempstr[opr].number = number2.time(opr);
				tempstr[opr].length = tempstr[opr].number.size();
			}
			while (opr < 9)
			{
				if (tempstr[opr + 1].number == "0")
				{
					tempstr[opr + 1].number = number2.time(opr + 1);
					tempstr[opr + 1].length = tempstr[opr + 1].number.size();
				}
				for (k = 0; k < tempstr[opr + 1].length&&number[k] == tempstr[opr + 1].number[k]; k++);
				if (tempstr[opr].length<number2.length + carry||k == tempstr[opr + 1].length || number[k] > tempstr[opr + 1].number[k]||tempstr[opr].length<number2.length+carry)//
				{
					opr++;
				}
				else
				{
					break;
				}
			}
			

			//minus 
			tempstr[10].length = number2.length+carry;
			tempstr[10].number = number.substr(0, tempstr[10].length);
			number=tempstr[10].sub(tempstr[opr])+ number.substr(tempstr[10].length,length- tempstr[10].length);
			loss = length-number.size()-1;
			if (loss> 0 &&carry)
			{
				loss--;
				carry = 0;
			}
			else if (loss < 0 && !carry)
			{
				loss++;
				carry = 1;
			}
			length = number.size();
			result.number += '0' + opr;

			//shift the remain
			
		}
		
		for (k = 0; k < length&&number[k] == '0'; loss++, k++);
		length -= k;
		number = number.substr(k, length);
		//add 0
		if (length >= number2.length)
		{
			for (k = 0; k < loss; k++)
			{
				result.number += '0';
			}
			result.length += loss;
		}
		else
		{
			for (k = 0; k < (loss + length) - number2.length+1; k++)
			{
				result.number += '0';
			}
			result.length += (loss + length) - number2.length;
		}
		
	}
	if (number == "")
	{
		number = "0";
	}
	return result.number;
}
