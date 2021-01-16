#pragma once
#include "Data.h"

class TrainData : public Data
{
	// http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
	// http://yann.lecun.com/exdb/mnist/train-labels-idx1-ubyte.gz

public:
	TrainData();
	virtual ~TrainData();
	void Load() override;
};

