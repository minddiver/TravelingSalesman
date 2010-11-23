#pragma once

#include "Base.h"

class Vertex : public Base {
public:
	Vertex();
	Vertex(Vertex* toCopy);
	~Vertex();
	Vertex(string label);
	string getLabel();
	void setLabel(string label);
	Vertex* copy();

private:
	string label;
};