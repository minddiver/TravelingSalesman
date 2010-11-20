#pragma once
#define PSEUDO NULL;
#include "Base.h"

using namespace std;



class Vertex : public Base {
public:
	Vertex();
	~Vertex();
	Vertex(char* label);
	char * getLabel();
	void setLabel(char * label);

private:
	char * label;



};