#pragma once

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Base {
public:
	//Base();
	//virtual ~Base();
	Base* getFirstP();
	Base* getSecondP();
	void setFirstP(Base* first);
	void setSecondP(Base* second);
protected:
	Base* firstP;
	Base* secondP;
	
};