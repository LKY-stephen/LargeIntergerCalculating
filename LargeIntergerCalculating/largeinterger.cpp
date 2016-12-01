#pragma once
#include "largeinterger.h"
#include<iostream>
using namespace std;

#define adjust(elem) elem->length=elem->number.size();

#define killzero(elem,len) for ( i = 0; i < len && elem->number[i] == '0'; i++); i==len?elem->number.erase(elem->number.begin(), elem->number.end()-1):i?elem->number.erase(elem->number.begin(), elem->number.begin()+i):number.begin();


Interger::Interger(char head)
{
	char  temp;
	number.clear();
	if (head == '-')
	{
		number.push_back('0');
		signal = false;
	}
	else if (head > '0'&&head <= '9')
	{
		number.push_back( head);
		signal = true;
	}
	else
	{
		number.push_back('0');
		signal = true;
	}
	
	while ((temp = getchar()) != '\n')
	{
		if (temp > '9' || temp < '0')
		{
			number.clear();
			number.push_back( 0x0);
			break;
		}
		else if (temp == '0')
		{
			if (number[0] == '0')
			{
				continue;
			}
			else
			{
				number.push_back(temp);
			}
		}
		else
		{
			if (number[0]=='0')
			{
				number[0]= temp;
			}
			number .push_back( temp);
		}
	}
	length=number.size();
}

Interger::Interger()
{
	number.push_back(0x0);
	length = 0;
	signal = true;
	return;
}
Interger::Interger(Interger & x)
{
	number = x.number;
	length = x.length;
	signal = x.signal;
	return;
}

Interger & Interger::operator=(const Interger & old)
{
	// TODO: 在此处插入 return 语句
	if (*this == old)
	{
		return *this;
	}
	if (number.size())
	{
		number.clear();
	}
	number.insert(number.begin(), old.number.begin(), old.number.end());
	length = old.length;
	signal = old.signal;
	return *this;
}

bool  Interger::operator==(const Interger & old)
{
	if (this->signal != old.signal || this->length != old.length)
	{
		return false;
	}
	int max = length;
	if (max != 0)
	{
		for (int i = 0; i < max; i++)
		{
			if (number[i] != old.number[i])
			{
				return false;
			}
		}
	}
	return true;
	// TODO: 在此处插入 return 语句
}


Interger Interger::add(Interger number2)
{
	char carry=0x0;
	char temp=0;
	Interger answer;
	Interger tempint;
	bool tempflag = false;
	if (number2.length > length)
	{
		tempflag = true;
		tempint = number2;
		number2 = *this;
		*this = tempint;
	}
	answer.number.clear();
	answer.signal = signal;
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
		answer.number.insert(answer.number.begin(), temp);
		iterator1--;
		iterator2--;
	}
	//add the large part
	if (carry == 0x0)
	{   //no carrybit
	    if (iterator1 >= 0)
		{
			answer.number.insert(answer.number.begin(), number.begin(), number.begin() + iterator1 + 1);
		}
		else if (iterator2 >= 0)
		{
			answer.number.insert(answer.number.begin(), number2.number.begin(), number2.number.begin() + iterator2 + 1);
		}
	}
	else
	{   //carry bit
		if (iterator1 >= 0)
		{//number1 has left
			size_t i;
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
				answer.number.insert(answer.number.begin(), number.begin(), number.begin() + iterator1 + 1);
			}
			else
			{
				answer.number.insert(answer.number.begin(), number.begin(), number.begin() + iterator1 + 1);
				answer.number.insert(answer.number.begin(), '1');
			}
			
		}//endif
		else if (iterator2 >= 0)
		{
			size_t i;
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
				answer.number.insert(answer.number.begin(), number2.number.begin(), number2.number.begin() + iterator1 + 1);
			}
			else
			{
				answer.number.insert(answer.number.begin(), number2.number.begin(), number2.number.begin() + iterator1 + 1);
				answer.number.insert(answer.number.begin(), '1');
			}

		}//end elseif
		else
		{
			answer.number.insert(answer.number.begin(),1);
		}//end else
	}
	answer.length = answer.number.size();
	if (tempflag)
	{
		tempint = number2;
		number2 = *this;
		*this = tempint;
	}
	return answer;
}

vector<unsigned char> Interger::sub(Interger number2)
{
	bool answersignal;
	vector<unsigned char> answer ;
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
		for (i = 0; i<length&&number[i] == number2.number[i]; i++);
		if (i == length)
		{
			answer.push_back('0');
			return answer;
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
				for (size_t j = iterator1-1; j >= 0; j--)
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
			answer.insert(answer.begin(),temp);
			iterator1--;
			iterator2--;
		}//endwhile
		if (iterator1 >= 0)
		{
			answer.insert(answer.begin(),number.begin(),number.begin() + iterator1 + 1);
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
				for (size_t j = iterator1-1; j >= 0; j--)
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
			answer.insert(answer.begin(), temp);
			iterator1--;
			iterator2--;
		}//endwhile
		if (iterator1 >= 0)
		{
			answer.insert(answer.begin(), number2.number.begin(), number2.number.begin() + iterator1 + 1);
		}
	}
	for (unsigned int i = 0; i < answer.size(); i++)
	{
		if (answer[i] != '0')
		{
			answer.erase(answer.begin(), answer.begin()+i);
			break;
		}
	}
	if (!answersignal)
	{
		answer.insert(answer.begin(), '-');
	}
	return answer;
}

Interger Interger::time(Interger* number2)
{
	Interger tempint;
	bool tempflag = false;
	if (number2->length > length)
	{
		tempflag = true;
		tempint = *number2;
		*number2 = *this;
		*this = tempint;
	}
	if (number2->length==1)
	{
		int y = (*(number2->number.begin()) - '0');
		Interger answer = singletime(y);
		if (tempflag)
		{
			tempint = *number2;
			*number2 = *this;
			*this = tempint;
		}
		return answer;
	}
	int i = 0, j = 0;
	Interger *tempstr[8];//x0,x1,y0,y1,z0,z1,z2,answer
	for (i = 0; i < 8; i++)
	{
		tempstr[i] = new Interger;
		tempstr[i]->number.clear();

	}
	int middle = length / 2;
	if (length == 2)
	{
		tempstr[0]->number.push_back(*number.begin()) ;
		tempstr[1]->number.push_back(*(number.end()-1));
		tempstr[2]->number.push_back((number2->length>1?*number2->number.begin(): '0'));
		tempstr[3]->number.push_back(*(number2->number.end() - 1));
	}
	else
	{
		tempstr[0]->number.insert(tempstr[0]->number.begin(), number.begin(), number.end()-middle);
		tempstr[1]->number.insert(tempstr[1]->number.begin(), number.end() - middle, number.end() );
		killzero(tempstr[1],middle)
	
		if (number2->length > middle)
		{
			tempstr[2]->number.insert(tempstr[2]->number.begin(), number2->number.begin(), number2->number.end() - middle);
			tempstr[3]->number.insert(tempstr[3]->number.begin(), number2->number.end() - middle, number2->number.end());
			killzero(tempstr[3], middle)
		}
		else
		{
			tempstr[3]->number = number2->number;
			tempstr[2]->number.push_back('0');
		}
	}
	
	
	for (i = 0; i < 4; i++)
	{
		tempstr[i]->length = tempstr[i]->number.size();
		tempstr[i]->signal = true;
	}
	tempstr[6]->number.swap(tempstr[0]->time(tempstr[2]).number);//z2=x0*y0
	adjust(tempstr[6])
	tempstr[4]->number.swap((tempstr[1]->time(tempstr[3]).number));//z0=x1*y1
	adjust(tempstr[4])
	tempstr[7]->number.swap(tempstr[3]->add(*tempstr[2]).number);//y1+x1
	adjust(tempstr[7])
	tempstr[5]->number.swap((tempstr[1]->add(*tempstr[0])).time(tempstr[7]).number);//z1
	adjust(tempstr[5])
	tempstr[7]->number .swap(tempstr[5]->sub(tempstr[4]->add(*tempstr[6])));//z1-z0-z2
	adjust(tempstr[7])
	for (int i = 0; i < middle; i++)
	{
		tempstr[6]->number.insert(tempstr[6]->number.end(), '0');
		tempstr[7]->number.insert(tempstr[7]->number.end(), '0');
		tempstr[6]->number.insert(tempstr[6]->number.end(), '0');
	}
	tempstr[6]->length = tempstr[6]->number.size();
	killzero(tempstr[6], tempstr[6]->length)
	adjust(tempstr[6])
	tempstr[7]->length = tempstr[7]->number.size();
	killzero(tempstr[7], tempstr[7]->length)
	adjust(tempstr[7])
	tempstr[7]->number.swap((((tempstr[6]->add(*tempstr[7]))).add(*tempstr[4])).number);
	adjust(tempstr[7])
	for (i = 0; i < 7; i++)
	{
		delete tempstr[i];
	}
	if (tempflag)
	{
		tempint = *number2;
		*number2 = *this;
		*this = tempint;
	}
	return *tempstr[7];
	
}

Interger Interger::singletime(int y)
{
	int carryb = 0, leftb, opr, tempb = 0;
	char temp;
	Interger answer;
	answer.number.clear();
	if (y == 0)
	{
		answer.number.push_back('0');
		answer.length++;
		return answer;
	}
	else if (y == 1)
	{
		answer.number = number;
		answer.length = length;
		return answer;
	}
	for (int i = length - 1; i >= 0; i--)
	{
		opr = number[i] - '0';
		tempb = opr*y + carryb;
		leftb = tempb % 10;
		carryb = (tempb - leftb) / 10;
		temp = leftb + '0';
		answer.number.insert(answer.number.begin(),temp);
	}
	if (carryb)
	{
		temp = carryb + '0';
		answer.number.insert(answer.number.begin(), temp);
	}
	answer.length = answer.number.size();
	return answer;
}



vector<unsigned char> Interger::divide(Interger number2)
{
	
	signal = (signal^number2.signal?false:true);
	Interger result;
	result.signal = signal;
	Interger tempstr[11];
	vector<unsigned char> *tempvec;
	int j,k,opr,loss,carry=0;
	char mark= signal ? 0x0 : '-';
	
	
	if (number2.length > length)
	{
		result.number[0] = '0';
		return result.number;
	}
	while ( length >= number2.length)
	{
		loss = 0;
		for ( j = 0; j < number2.length&&number[j] == number2.number[j]; j++);
		if (j == number2.length)// if all the number is equal to number2
		{
			number.erase(number.begin(), number.begin()+number2.length);
			length -= number2.length;
			result.number.push_back('1');
			result.length += number2.length;
			loss = number2.length - 1;
		}
		else 
		{
			if ((number[0] < number2.number[0]) || (j > 0 && number[j] < number2.number[j]))
			{
				if (result.number[0] != 0x0&&carry==0)
				{
					result.number.push_back('0');
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
			
			if (tempstr[opr].number[0]=='0')
			{
				tempstr[opr] = number2.singletime(opr);
			}
			while (opr < 9)
			{
				if (tempstr[++opr].number[0] == '0')
				{
					tempstr[opr] = number2.singletime(opr);
				}
				for (k = 0; k < tempstr[opr].length&&number[k] == tempstr[opr].number[k]; k++);
				if (tempstr[opr-1].length<number2.length + carry||k == tempstr[opr].length || number[k] > tempstr[opr].number[k]||tempstr[opr-1].length<number2.length+carry)//
				{
					continue;
				}
				else
				{
					opr--;
					break;
				}
			}
			

			//minus 
			tempstr[10].length = number2.length+carry;
			tempstr[10].number.clear();
			tempstr[10].number .insert(tempstr[10].number.begin(),number.begin(),number.begin()+tempstr[10].length);
			number.clear();
			tempvec=&tempstr[10].sub(tempstr[opr]);
			number.insert(number.end(), tempvec->begin(), tempvec->end());
		    number.insert(number.end(),number.begin()+tempstr[10].length,number.end());
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
			result.number .push_back ('0' + opr);

			//shift the remain
			
		}
		
		for (k = 0; k < length&&number[k] == '0'; loss++, k++);
		length -= k;
		number.erase(number.begin(),number.begin()+k);
		//add 0
		if (length >= number2.length)
		{
			for (k = 0; k < loss; k++)
			{
				result.number.push_back('0');
			}
			result.length += loss;
		}
		else
		{
			for (k = 0; k < (loss + length) - number2.length+1; k++)
			{
				result.number .push_back( '0');
			}
			result.length += (loss + length) - number2.length;
		}
		
	}
	if (number[0]==0x0)
	{
		number[0]='0';
	}
	return result.number;
}
