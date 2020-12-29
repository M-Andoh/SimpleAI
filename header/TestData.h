#pragma once
#include "Data.h"

class TestData : public Data
{
	// http://yann.lecun.com/exdb/mnist/
	// http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
	// http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz
	// http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz
	// http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz

public:
	TestData();
	virtual ~TestData();
};

