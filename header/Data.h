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

	double** Images;	// �摜�f�[�^ 
	double** Answers;	// �w�K�p�̉𓚃f�[�^
	int* AnsNumber;     // �� �� ���l

	Data();
	virtual ~Data();
	void Load();

	bool GetFile(std::string& file, std::string& url);
	bool Decompress(std::string& file, std::string& tmpfile);

};




