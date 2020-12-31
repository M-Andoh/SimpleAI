#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string>
#include <iostream>
#include <fstream>
#include <exception>
#include "TestData.h"
#include "mkbmp.h"


TestData::TestData() {
	TrainDataNum = 0;
	TestDataNum = 10000;

	std::string imageUrl = "http://yann.lecun.com/exdb/mnist/t10k-images-idx3-ubyte.gz";
	std::string imageTempName = "t10k-images-idx3-ubyte.gz";
	std::string imageFileName = "t10k-images-idx3-ubyte";
	std::string labelUrl = "http://yann.lecun.com/exdb/mnist/t10k-labels-idx1-ubyte.gz";
	std::string labelTempName = "t10k-labels-idx1-ubyte.gz";
	std::string labelFileName = "t10k-labels-idx1-ubyte";

	{
		char buffer[PATH_MAX];
		char* filename = realpath(imageFileName.c_str(), buffer);

		std::cerr << filename << std::endl;
		std::ifstream ifs(imageFileName);
		if (!ifs.is_open()) {
			if (!GetFile(imageTempName, imageUrl)) {
				throw std::invalid_argument("file download error : " + imageUrl);
			}
			Decompress(imageFileName, imageTempName);
			unlink(imageTempName.c_str());
		}
		ifs.close();
		TestFileName = imageFileName;
	}

	{
		char buffer[PATH_MAX];
		char* filename = realpath(labelFileName.c_str(), buffer);

		std::cerr << filename << std::endl;
		std::ifstream ifs(labelFileName);
		if (!ifs.is_open()) {
			if (!GetFile(labelTempName, labelUrl)) {
				throw std::invalid_argument("file download error : " + labelUrl);
			}
			Decompress(labelFileName, labelTempName);
			unlink(labelTempName.c_str());
		}
		ifs.close();
		LabelFileName = labelFileName;
	}
	// std::cout << "TrainData,constructor" << std::endl;
}

TestData::~TestData() {
	// std::cout << "TrainData,destructor" << std::endl;
}

