#pragma once
#include <string>

using namespace std;

class Interger{
public:
	string number;//save the number
	int length;//save the length
	bool signal;//save the signal of the number
	
	Interger();//init function

	string add(Interger number2);//add same signal number2
	string sub(Interger number2);//minus number2
	string time(Interger number2);//time number2
	string divide(Interger number2);//divided by number2

};