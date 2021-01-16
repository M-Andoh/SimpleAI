#include "Data.h"
#include <iostream>
#include <fstream>
#include "TrainData.h"
#include "mkbmp.h"


Data::Data() :
	Images(nullptr), Answers(nullptr), AnsNumber(nullptr)
{
	// std::cout << "TrainData,constructor" << std::endl;
}

Data::~Data() {
	// std::cout << "TrainData,destructor" << std::endl;
	int num = Data::TrainDataNum + Data::TestDataNum;
	if (Images != nullptr) {
		for (int i = 0; i < num; ++i) {
			delete[] Images[i];
		}
	}
	if (Answers != nullptr) {
		for (int i = 0; i < num; ++i) {
			delete[] Answers[i];
		}
	}
	delete[] Images;
	delete[] Answers;
	delete[] AnsNumber;
}


size_t callBackFunk(char* ptr, size_t size, size_t nmemb, std::ofstream* ofs)
{
	int realsize = (int)size * (int)nmemb;
	ofs->write(ptr, realsize);
	return realsize;
}

bool Data::GetFile(std::ostream& ofs, std::string& url) {
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	if (!curl)
	{
		std::cout << "curl initialize error" << std::endl;
		return false;
	}

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (std::ofstream*)&ofs);
	curl_easy_setopt(curl, CURLOPT_PROXY, "");
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (res != CURLE_OK) {
		std::cout << "curl error" << std::endl;
		exit(1);
	}

	return true;
}

bool Data::GetFileByPost(std::ostream& ofs, std::string& url, std::string _contentType, std::string postData) {
	CURL* curl;
	CURLcode res;
	curl = curl_easy_init();

	if (!curl)
	{
		std::cout << "curl initialize error" << std::endl;
		return false;
	}

	struct curl_slist* chunk = NULL;
	std::string contentType = "Content-Type: " + _contentType;
	chunk = curl_slist_append(chunk, contentType.c_str());
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postData.c_str());
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)postData.length());
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callBackFunk);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (std::ofstream*)&ofs);
	curl_easy_setopt(curl, CURLOPT_PROXY, "");

	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);

	if (res != CURLE_OK) {
		std::cout << "curl error" << std::endl;
		exit(1);
	}

	return true;
}

bool Data::Decompress(std::string& filename, std::string& gzfile) {
	gzFile gzf = gzopen(gzfile.c_str(), "rb");
	std::ofstream ofs(filename, std::ios::binary);
	int readbytes;
	char buffer[4096];

	if (gzf == NULL) {
		std::cerr << "file open error : " << gzfile << std::endl;
		return false;
	}

	if (!ofs.is_open()) {
		std::cerr << "file open error : " << filename << std::endl;
		return false;
	}

	while ((readbytes = gzread(gzf, buffer, 4096)) > 0) {
		ofs.write(buffer, readbytes);
	}

	gzclose(gzf);
	ofs.close();
	return true;
}

void Data::Load() {
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
