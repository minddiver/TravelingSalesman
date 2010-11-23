#include "Vertex.h"

Vertex::Vertex() {
	this->label = string("");
}

Vertex::Vertex(Vertex* toCopy) 
{
	this->setLabel(toCopy->getLabel());
	this->setMarked(toCopy->isMarked());
}

//Vertex::~Vertex() {}

Vertex::Vertex(string label) {
	this->label = label;
}


string Vertex::getLabel() {
	return this->label;
}

void Vertex::setLabel(string label) {
	this->label = label;
}

Vertex* Vertex::copy() 
{
	return new Vertex(this);
}

