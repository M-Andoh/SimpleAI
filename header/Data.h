#pragma once
#include <string>
#include <fstream>
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
	virtual void Load();

	bool GetFile(std::ostream& ofs, std::string& url);
	bool GetFileByPost(std::ostream& ofs, std::string& url, std::string contentType, std::string postData);
	bool Decompress(std::string& file, std::string& tmpfile);

};




