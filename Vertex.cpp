#pragma once
#include "Base.h"
#include "Vertex.h"

Vertex::Vertex() {
	this->label = "";
}

string Vertex::getLabel() {
	return this->label;
}

void Vertex::setLabel(std::string label) {
	this->label = label;
}

