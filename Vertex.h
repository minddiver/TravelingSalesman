#pragma once
#define PSEUDO NULL;
#include "Base.h"
using namespace std;


class Vertex : public Base {
public:
	Vertex();
	~Vertex();
	Vertex(string label);
	string getLabel();
	void setLabel(string label);
	Vertex* getNext();
	void setNext(Vertex* next);
	Base* getEdge();
	void setEdge(Base* edge);

private:
	string label;
};