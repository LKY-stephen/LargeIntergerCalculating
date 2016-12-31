#pragma once
#include "largeinterger.h"
#include<iostream>
#include<assert.h>
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


void Interger::add(Interger *number2, Interger *answer)
{
	char carry=0x0;
	char temp=0;
	Interger tempint;
	bool tempflag = false;
	if (number2->length > length)
	{
		tempflag = true;
		tempint =* number2;
		*number2 = *this;
		*this = tempint;
	} 
	//exchange number to make sure number1 is bigger than number 2
	answer->signal = signal;
	int iterator1 = length - 1;
	int iterator2 = number2->length - 1;
	//add the small number
	while (iterator1 >= 0 && iterator2 >= 0)
	{
		temp = carry+number[iterator1] + number2->number[iterator2]-'0'-'0';
		if (temp > 0x09)
		{
			carry = 0x1;
			temp -= 10;
		}
		else
		{
			carry = 0x0;
		}
		answer->number.insert(answer->number.begin(), temp+'0');
		iterator1--;
		iterator2--;
	}
	//add the large part
	if (carry == 0x0)
	{   //no carrybit
	    if (iterator1 >= 0)
		{
			answer->number.insert(answer->number.begin(), number.begin(), number.begin() + iterator1 + 1);
		}
		else if (iterator2 >= 0)
		{
			answer->number.insert(answer->number.begin(), number2->number.begin(), number2->number.begin() + iterator2 + 1);
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
					answer->number.insert(answer->number.begin(),number[i]+1);
					break;//break for
				}
				answer->number.insert(answer->number.begin(),'0');
			}
			if (i >= 0)
			{
				answer->number.insert(answer->number.begin(), number.begin(), number.begin() +i);
			}
			else
			{
				answer->number.insert(answer->number.begin(), '1');
			}
			
		}//endif
		else if (iterator2 >= 0)
		{
			int i;
			for (i = iterator2; i >= 0; i--)
			{
				if (number2->number[i] != '9')
				{
					answer->number.insert(answer->number.begin(), number2->number[i] + 1);
					break;//break for
				}
				answer->number.insert(answer->number.begin(), '0');
			}
			if (i > 0)
			{
				answer->number.insert(answer->number.begin(), number2->number.begin(), number2->number.begin() + i);
			}
			else if (i < 0)
			{
				answer->number.insert(answer->number.begin(), '1');
				
			}

		}//end elseif
		else
		{
			answer->number.insert(answer->number.begin(),'1');
		}//end else
	}
	for (int m = 0; m < answer->number.size(); m++)
	{
		assert(answer->number[m] >= '0'&&answer->number[m] <= '9');
	}
	answer->length = answer->number.size();
	if (tempflag)
	{
		tempint = *number2;
		*number2 = *this;
		*this = tempint;
	}
}

void Interger::sub(Interger *number2, Interger *answer)
{
	bool answersignal;
	char temp = '0';
	int iterator1;
	int iterator2;
	int tempup=-1;
	int temppos = 0;
	//decide the sgn
	if (length > number2->length)
	{
		answersignal = true;
	}
	else if (length < number2->length)
	{
		answersignal = false;
	}
	else
	{
		int i=0;
		for (i = 0; i<length&&number[i] == number2->number[i]; i++);
		if (i == length)
		{
			answer->number.push_back('0');
			answersignal = true;
			return;
		}
		else
		{
			answersignal = number[i] > number2->number[i] ? true : false;
		}
	}
	if (answersignal)
	{
		iterator2 = number2->length - 1;
		iterator1 = length - 1;
		while (iterator2 >= 0)
		{
			if (temppos > 1)
			{
				temp = ('9' - number2->number[iterator2]) + '0';
				temppos--;
			}
			else if (temppos == 1)
			{
				temppos--;
				if (tempup < number2->number[iterator2])
				{
					temp = (tempup - number2->number[iterator2] + 10) + '0';
					tempup = -1;
					for (int j = iterator1 - 1; j >= 0; j--)
					{
						if (number[j] > '0')
						{
							tempup = number[j] - 1;
							temppos++;
							break;//break for
						}
						temppos++;
					}

				}//endif
				else
				{
					temp = (tempup - number2->number[iterator2]) + '0';
					tempup = -1;
				}
			}
			else
			{
				if (number[iterator1] < number2->number[iterator2])
				{
					for (int j = iterator1 - 1; j >= 0; j--)
					{
						if (number[j] > '0')
						{
							tempup = number[j] - 1;
							temppos++;
							break;//break for
						}
						temppos++;
					}
					temp = (number[iterator1] - number2->number[iterator2] + 10) + '0';
				}//endif
				else
				{
					temp = (number[iterator1] - number2->number[iterator2]) + '0';
				}
				
			}//endif-else
			answer->number.insert(answer->number.begin(), temp);
			iterator1--;
			iterator2--;
			
		}//end while
		
			if (temppos)
			{
				for (; temppos > 1; temppos--)
				{
					answer->number.insert(answer->number.begin(), '9');
					iterator1--;
				}
				answer->number.insert(answer->number.begin(), tempup);
				iterator1--;
				if (iterator1 >= 0)
				{
					answer->number.insert(answer->number.begin(), number.begin(), number.begin() + iterator1 + 1);
				}
			}
			
	}//end answersignal==true
	else
	{
		iterator1 = number2->length - 1;
		iterator2 = length - 1;
		while (iterator2 >= 0)
		{
			if (temppos > 1)
			{
				temppos--;
				temp = ('9' - number[iterator2]) + '0';
			}
			else if(temppos == 1)
			{
				temppos--;
				if (tempup< number[iterator2])
				{
					temp = (tempup - number[iterator2] + 10) + '0';
					tempup = -1;
					for (int j = iterator1 - 1; j >= 0; j--)
					{
						if (number2->number[j] > '0')
						{
							tempup = number2->number[j] - 1;
							temppos++;
							break;//break for
						}
						temppos++;
					}
				
				}//endif
				else
				{
					temp = (tempup- number[iterator2]) + '0';
					tempup = -1;
				}
			}
			else 
			{
				if (number2->number[iterator1] < number[iterator2])
				{
					for (int j = iterator1 - 1; j >= 0; j--)
					{
						if (number2->number[j] > '0')
						{
							tempup = number2->number[j] - 1;
							temppos++;
							break;//break for
						}
						temppos++;
					}
					temp = (number2->number[iterator1] - number[iterator2] + 10) + '0';
				}//endif
				else
				{
					temp = (number2->number[iterator1] - number[iterator2]) + '0';
				}
				
			}
			answer->number.insert(answer->number.begin(), temp);
			iterator1--;
			iterator2--;
		}//endwhile
		if (temppos)
		{
			for (; temppos > 1; temppos--)
			{
				answer->number.insert(answer->number.begin(), '9');
				iterator1--;
			}
			answer->number.insert(answer->number.begin(), tempup );
			iterator1--;
			if (iterator1 >= 0)
			{
				answer->number.insert(answer->number.begin(), number2->number.begin(), number2->number.begin() + iterator1 + 1);
			}
		}
	}
	for (unsigned int i = 0; i < answer->number.size(); i++)
	{
		if (answer->number[i] != '0')
		{
			answer->number.erase(answer->number.begin(), answer->number.begin()+i);
			break;
		}
	}
	if (!answersignal)
	{
		answer->signal=false;
	}
}

void Interger::time(Interger *number2, Interger *answer)
{
	Interger *tempint= new Interger;
	bool tempflag = false;
	if (number2->length > length)
	{
		tempflag = true;
		*tempint = *number2;
		*number2 = *this;
		*this = *tempint;
	}
	if (number2->length==1)
	{
		int y = (*(number2->number.begin()) - '0');
		singletime(y,answer);
		if (tempflag)
		{
			*tempint = *number2;
			*number2 = *this;
			*this = *tempint;
		}
		return;
	}
	int i = 0, j = 0;
	Interger *tempstr[7];//x0,x1,y0,y1,z0,z1,z2
	for (i = 0; i < 7; i++)
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
	tempstr[6]->number.clear();
	tempstr[0]->time(tempstr[2], tempstr[6]);//z2=x0*y0
	adjust(tempstr[6])
	tempstr[4]->number.clear();
	tempstr[1]->time(tempstr[3],tempstr[4]);//z0=x1*y1
	adjust(tempstr[4])
	answer->number.clear();
	tempstr[3]->add(tempstr[2],answer);//y1+y0
	adjust(answer)
	tempint->number.clear();
	tempstr[1]->add(tempstr[0], tempint);//x1+x0
	tempstr[5]->number.clear();
	adjust(tempint)
	tempint->time(answer, tempstr[5]);//z1
	adjust(tempstr[5])
	tempint->number.clear();
	answer->number.clear();
	tempstr[4]->add(tempstr[6], tempint);
	adjust(tempint)
	tempstr[5]->sub(tempint, answer);//z1-z0-z2
	adjust(answer)
	for (int i = 0; i < middle; i++)
	{
		tempstr[6]->number.insert(tempstr[6]->number.end(), '0');
		answer->number.insert(answer->number.end(), '0');
		tempstr[6]->number.insert(tempstr[6]->number.end(), '0');
	}
	tempstr[6]->length = tempstr[6]->number.size();
	killzero(tempstr[6], tempstr[6]->length)
	adjust(tempstr[6])
	killzero(answer, answer->length)
	adjust(answer)
	tempint->number.clear();
	tempstr[6]->add(answer, tempint);
	answer->number.clear();
	tempint->add(tempstr[4], answer);
	adjust(answer)
	for (i = 0; i < 7; i++)
	{
		delete tempstr[i];
	}
	delete tempint;
	if (tempflag)
	{
		*tempint = *number2;
		*number2 = *this;
		*this = *tempint;
	}
	return ;
	
}

void Interger::singletime(int y, Interger *answer)
{
	int carryb = 0, leftb, opr, tempb = 0;
	char temp;
	if (y == 0)
	{
		answer->number.push_back('0');
		answer->length++;
		return;
	}
	else if (y == 1)
	{
		answer->number = number;
		answer->length = length;
		return;
	}
	for (int i = length - 1; i >= 0; i--)
	{
		opr = number[i] - '0';
		tempb = opr*y + carryb;
		leftb = tempb % 10;
		carryb = (tempb - leftb) / 10;
		temp = leftb + '0';
		answer->number.insert(answer->number.begin(),temp);
	}
	if (carryb)
	{
		temp = carryb + '0';
		answer->number.insert(answer->number.begin(), temp);
	}
	answer->length = answer->number.size();
}



void Interger::divide(Interger *number2, Interger *answer)
{
	
	signal = (signal^number2->signal?false:true);
	answer->signal = signal;
	Interger tempstr[11];
	Interger *tempvec=new Interger;
	int j,k,opr,loss,carry=0;
	char mark= signal ? 0x0 : '-';
	
	
	if (number2->length > length)
	{
		answer->number[0] = '0';
	}
	while ( length >= number2->length)
	{
		loss = 0;
		for ( j = 0; j < number2->length&&number[j] == number2->number[j]; j++);
		if (j == number2->length)// if all the number is equal to number2
		{
			number.erase(number.begin(), number.begin()+number2->length);
			length -= number2->length;
			answer->number.push_back('1');
			answer->length += number2->length;
			loss = number2->length - 1;
		}
		else 
		{
			if ((number[0] < number2->number[0]) || (j > 0 && number[j] < number2->number[j]))
			{
				if (answer->number[0] != 0x0&&carry==0)
				{
					answer->number.push_back('0');
					answer->length++;
				}
				opr = ((number[0] - '0') * 10 + (number[1] - '0')) / (number2->number[0] - '0' + 1);
				carry = 1;
			}
			else
			{
				opr = (number[0] - '0') / (number2->number[1] - '0' + 1);
			}
			
			//determin the value of result
			
			if (tempstr[opr].number[0]=='0')
			{
				number2->singletime(opr, &tempstr[opr]);
			}
			while (opr < 9)
			{
				if (tempstr[++opr].number[0] == '0')
				{
					number2->singletime(opr, &tempstr[opr]);
				}
				for (k = 0; k < tempstr[opr].length&&number[k] == tempstr[opr].number[k]; k++);
				if (tempstr[opr-1].length<number2->length + carry||k == tempstr[opr].length || number[k] > tempstr[opr].number[k]||tempstr[opr-1].length<number2->length+carry)//
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
			tempstr[10].length = number2->length+carry;
			tempstr[10].number.clear();
			tempstr[10].number .insert(tempstr[10].number.begin(),number.begin(),number.begin()+tempstr[10].length);
			number.clear();
			tempstr[10].sub(&tempstr[opr],tempvec);
			number.insert(number.end(), tempvec->number.begin(), tempvec->number.end());
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
			answer->number .push_back ('0' + opr);

			//shift the remain
			
		}
		
		for (k = 0; k < length&&number[k] == '0'; loss++, k++);
		length -= k;
		number.erase(number.begin(),number.begin()+k);
		//add 0
		if (length >= number2->length)
		{
			for (k = 0; k < loss; k++)
			{
				answer->number.push_back('0');
			}
			answer->length += loss;
		}
		else
		{
			for (k = 0; k < (loss + length) - number2->length+1; k++)
			{
				answer->number .push_back( '0');
			}
			answer->length += (loss + length) - number2->length;
		}
		
	}
	if (number[0]==0x0)
	{
		number[0]='0';
	}
	delete tempvec;
}
