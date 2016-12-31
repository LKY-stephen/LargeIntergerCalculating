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

	void add(Interger *number2, Interger *answer);//add same signal number2
	void sub(Interger *number2, Interger *answer);//minus number2
	void time(Interger *number2, Interger *answer);//time number2
	void singletime(int y, Interger *answer);
	void divide(Interger *number2, Interger *answer);//divided by number2

};