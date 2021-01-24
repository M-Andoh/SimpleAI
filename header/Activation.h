#pragma once
#include "string"

class Activation
{
public:
	std::string name;
	virtual double forword(double) = 0;
	virtual double backword(double) = 0;

	Activation(std::string _name) : name(_name) {}
};

