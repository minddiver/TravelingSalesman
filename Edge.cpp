#include "Edge.h"

Edge::Edge() {
	this->weight = 0;
}

Edge::Edge(Edge* toCopy)
{
	this->setWeight(toCopy->getWeight());
	this->setMarked(toCopy->isMarked());
}

Edge::~Edge() {}


Edge::Edge(int weight) {
	this->weight = weight;
}

int Edge::getWeight() {
	return this->weight;
}

void Edge::setWeight(int weight) {
	this->weight = weight;
}

Edge* Edge::copy() 
{
	return new Edge(this);
}
