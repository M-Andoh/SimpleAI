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
			std::ofstream ofs(imageTempName);
			if (!ofs) {
				std::cout << "fileopen error" << std::endl;
				throw std::invalid_argument("file download error : " + imageUrl);
			}

			if (!GetFile(ofs, imageUrl)) {
				throw std::invalid_argument("file download error : " + imageUrl);
			}
			ofs.close();

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
			std::ofstream ofs(labelTempName);
			if (!ofs) {
				std::cout << "fileopen error" << std::endl;
				throw std::invalid_argument("file download error : " + imageUrl);
			}

			if (!GetFile(ofs, labelUrl)) {
				throw std::invalid_argument("file download error : " + labelUrl);
			}
			ofs.close();

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

void TestData::Load() {
	int num = Data::TrainDataNum + Data::TestDataNum;
	Images = new double* [num];
	Answers = new double* [num];
	AnsNumber = new int[num];

	// 画像データの読み込み
	std::ifstream ifs(TestFileName);
	if (!ifs) {
		std::cerr << "file open error : " << TestFileName << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// ヘッダ部が16byteあるので読み飛ばす
	{
		char tmp[16];
		ifs.read(tmp, 16);
	}

	for (int cnt = 0; cnt < num; cnt++) {
		Images[cnt] = new double[28 * 28];
		unsigned char tmp[28 * 28];
		ifs.read((char*)tmp, sizeof(tmp));
		// ファイルには0～255のデータが入っている
		// これを0～1.0に変換する
		for (size_t i = 0; i < sizeof(tmp); ++i) {
			Images[cnt][i] = ((double)tmp[i] / 255.0);
		}
	}
	ifs.close();

	// 答えデータの読み込み
	ifs.open(LabelFileName);
	if (!ifs) {
		std::cerr << "file open error : " << LabelFileName << std::endl;
		std::exit(EXIT_FAILURE);
	}

	// ヘッダ部8byteを読み飛ばす
	// ヘッダ部が16byteあるので読み飛ばす
	{
		char tmp[8];
		ifs.read(tmp, 8);
		std::cout << tmp << std::endl;
	}

	for (int cnt = 0; cnt < num; ++cnt) {
		char tmp;
		ifs.read(&tmp, 1);
		AnsNumber[cnt] = tmp;

		// double[10]の配列を作成し、答えのIndex位置を1.0にする
		Answers[cnt] = new double[10];
		for (int i = 0; i < 10; ++i) {
			Answers[cnt][i] = 0.0;
		}
		Answers[cnt][(int)tmp] = 1.0;
	}
#ifdef MKBMP
	for (int cnt = 0; cnt < num; ++cnt) {
		mkbmp(cnt, (int)AnsNumber[cnt], Images[cnt]);
	}
#endif // DEBUG
}
