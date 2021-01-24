#include "ReLU.h"
#include "math.h"

ReLU relu;

ReLU::ReLU() : Activation("ReLU") {
}

double ReLU::forword(double d)
{
	return ((d > 0) ? d : 0.0);
}

double ReLU::backword(double d)
{
	return ((d > 0) ? 1.0 : 0.0);
}
