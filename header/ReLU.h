#pragma once
#include "Activation.h"

class ReLU : public Activation
{
public:
	ReLU();
	virtual ~ReLU() = default;
	ReLU(const ReLU&) = delete;
	ReLU(ReLU&&) = delete;

	double forword(double) override;
	double backword(double) override;
};

extern ReLU relu;
