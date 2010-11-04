#pragma once
#include "Base.h"

Base::Base() {
	this->firstP = PSEUDO;
	this->secondP = PSEUDO;
	this->flag = false;
}

Base* Base::getFirstP() {
	return this->firstP;
}

Base* Base::getSecondP() {
	return this->secondP;
}

void Base::setFirstP(Base *first) {
	this->firstP = first;
}

void Base::setSecondP(Base *second) {
	this->secondP;
}

bool Base::getFlag() {
	return this->flag;
}

void Base::setFlag(bool flag) {
	this->flag = flag;
}
