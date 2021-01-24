#pragma once
#include "Activation.h"

class Sigmoid : public Activation
{
public:
	Sigmoid();
	virtual ~Sigmoid() = default;
	Sigmoid(const Sigmoid&) = delete;
	Sigmoid(Sigmoid&&) = delete;

	double forword(double) override;
	double backword(double) override;
};

extern Sigmoid sigmoid;
