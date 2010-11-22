#include "Edge.h"

Edge::Edge() {
	this->weight = 0;
}

Edge::Edge(int weight) {
	this->weight = weight;
}

int Edge::getWeight() {
	return this->weight;
}

void Edge::setWeight(int weight) {
	this->weight = weight;
}

Edge* Edge::getNext() {
	return (Edge*)this->getSecondP();
}

void Edge::setNext(Edge* next) {
	this->setSecondP(next);
}

Base* Edge::getTarget() {
	return this->getFirstP();
}

void Edge::setTarget(Base* target) {
	this->setFirstP(target);
}