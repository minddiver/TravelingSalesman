#pragma once
#define PSEUDO NULL;
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
	Edge* getEdge();
	void setEdge(Edge* edge);

private:
	string label;
};