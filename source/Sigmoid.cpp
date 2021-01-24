#include "Sigmoid.h"
#include "math.h"

Sigmoid sigmoid;

Sigmoid::Sigmoid() : Activation("Sigmoid") {
}

double Sigmoid::forword(double d)
{
	return (1.0 / (1.0 + exp(-1.0 * d)));
}

double Sigmoid::backword(double d)
{
	return ((1.0 - d) * d);
}
