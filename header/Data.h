#pragma once
#include <string>
#include <curl/curl.h>
#include <zlib.h>

class Data
{

public:
	int TrainDataNum;
	int TestDataNum;
	std::string TestFileName;
	std::string LabelFileName;

	double** Images;	// 画像データ 
	double** Answers;	// 学習用の解答データ
	int* AnsNumber;     // 解答 の 数値

	Data();
	virtual ~Data();
	void Load();

	bool GetFile(std::string& file, std::string& url);
	bool Decompress(std::string& file, std::string& tmpfile);

};




