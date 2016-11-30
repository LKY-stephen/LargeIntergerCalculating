#pragma once
#include <string>

using namespace std;

class Interger{
public:
	string number;//save the number
	size_t length;//save the length
	bool signal;//save the signal of the number
	
	Interger(char head);//init function
	Interger();

	Interger add(Interger number2);//add same signal number2
	string sub(Interger number2);//minus number2
	Interger time(Interger number2);//time number2
	Interger singletime(int y);
	string divide(Interger number2);//divided by number2

};