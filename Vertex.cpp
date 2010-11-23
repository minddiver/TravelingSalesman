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

