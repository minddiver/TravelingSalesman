#pragma once
#include "Base.h"

using namespace std;

class Edge : public Base {
public:
	Edge();
	int getWeight();
	//virtual ~Edge(void);

private:
	int weight;
};