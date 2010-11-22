#pragma once
#include "Base.h"

Base::Base() {
	this->firstP = PSEUDO;
	this->secondP = PSEUDO;
	this->mark = false;
}

Base::~Base() {
	//if(this->firstP != NULL)
	//	delete this->firstP;

	//if(this->secondP != NULL)
	//	delete this->secondP;
}

Base* Base::getFirstP() {
	return this->firstP;
}

Base* Base::getSecondP() {
	return this->secondP;
}

bool Base::isMarked() {
	return this->mark;
}


void Base::setMarked(bool marked) {
	this->mark = marked;
}

void Base::setFirstP(Base *first) {
	this->firstP = first;
}

void Base::setSecondP(Base *second) {
	this->secondP = second;
}

