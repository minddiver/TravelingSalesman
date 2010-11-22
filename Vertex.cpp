#include "Vertex.h"

Vertex::Vertex() {
	this->label = string("");
}

Vertex::Vertex(string label) {
	this->label = label;
}

Vertex::~Vertex() {
	delete &this->label;
}

string Vertex::getLabel() {
	return this->label;
}

void Vertex::setLabel(string label) {
	this->label = label;
}

Vertex* Vertex::getNext() {
	return (Vertex*)this->getFirstP();
}

void Vertex::setNext(Vertex* next) {
	this->setFirstP(next);
}

Base* Vertex::getEdge() {
	return this->getSecondP();
}

void Vertex::setEdge(Base *edge) {
	this->setSecondP(edge);
}

