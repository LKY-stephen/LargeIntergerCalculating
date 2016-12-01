#pragma once
#include <vector>
#define MAXSIZE 1000
using namespace std;

class Interger{
public:
	vector<unsigned char> number;//save the number
	int length;//save the length
	bool signal;//save the signal of the number
	
	Interger(char head);//init function
	Interger();
	Interger(Interger & x);
	Interger& operator =(const Interger& old);
	bool operator ==(const Interger& old);

	Interger add(Interger number2);//add same signal number2
	vector<unsigned char> sub(Interger number2);//minus number2
	Interger time(Interger* number2);//time number2
	Interger singletime(int y);
	vector<unsigned char> divide(Interger number2);//divided by number2

};