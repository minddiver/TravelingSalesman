#pragma once

#include <iostream>
#include <string>

#define PSEUDO NULL
#define DEBUG_LEVEL 0

using namespace std;

/*
Der erste Zeiger zeigt immer auf einen Knoten.
Der zweite Zeiger zeigt immer auf eine Ecke.
*/
class Base {
public:
	Base();
	~Base();
	Base* getFirstP();
	Base* getSecondP();
	bool isMarked();
	void setFirstP(Base* first);
	void setSecondP(Base* second);
	void setMarked(bool marked);
private:
	Base* firstP;
	Base* secondP;
	bool mark;
};