#pragma once

#include "Base.h"

using namespace std;



class Vertex : public Base {
public:
	Vertex();
	string getLabel();
	void setLabel(string label);

private:
	string label;



};