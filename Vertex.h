#pragma once

#include "Base.h"

class Vertex : public Base {
public:
	Vertex();
	~Vertex();
	Vertex(string label);
	string getLabel();
	void setLabel(string label);

private:
	string label;
};