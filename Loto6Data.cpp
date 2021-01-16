#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <exception>
#include <time.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "Loto6Data.h"
#include "Loto6.h"

Loto6Data::Loto6Data() : Loto6Url("https://www.takarakujinet.co.jp/api/search/past_result.php")
{
	 TrainDataNum = 0;
	 TestDataNum = 0;
}

Loto6Data::~Loto6Data() {
	// std::cout << "TrainData,destructor" << std::endl;
}

void Loto6Data::Load() {
	std::string contentType = "application/json";

	time_t _time;
	time(&_time);
	struct tm* datetime;
	datetime = localtime(&_time);
	char date[12];
	sprintf(date, "%04d%02d%02d", 1900 + datetime->tm_year, 1 + datetime->tm_mon, datetime->tm_mday);

	{
		std::ostringstream oss;
		oss
			<< "{\"kuji_type\":4000, \"ymd\":\""
			<< date
			<< "\", \"howmany\":"
			<< 1
			<< "}";
		std::ostringstream ss;
		if (!GetFileByPost(ss, Loto6Url, contentType, oss.str())) {
			throw std::invalid_argument("file download error : " + Loto6Url);
		}
		json json1 = json::parse(ss.str());
		json jsonData = json1[0];

		TrainDataNum = jsonData["/kaigo"_json_pointer].get<int>();
		TestDataNum = 0;
	}

	int num = Data::TrainDataNum + Data::TestDataNum;
	Data = new Loto6[num];

	{
		std::ostringstream oss;
		oss
			<< "{\"kuji_type\":4000, \"ymd\":\""
			<< date
			<< "\", \"howmany\":"
			<< TrainDataNum
			<< "}";
		std::ostringstream ss;

		if (!GetFileByPost(ss, Loto6Url, contentType, oss.str())) {
			throw std::invalid_argument("file download error : " + Loto6Url);
		}
		// std::cerr << ss.str() << std::endl;
		json jsonAll = json::parse(ss.str());
		int i = 0;
		std::vector<Loto6> array;
		for (json::reverse_iterator it = jsonAll.rbegin(); it != jsonAll.rend(); ++it, ++i) {
			json jsonData = *it;
			Data[i].kaigou = jsonData["/kaigo"_json_pointer].get<int>();
			// std::cerr << Data[i].kaigou << std::endl;
			Data[i].tousen[atoi(jsonData["/tousen/1"_json_pointer].get<std::string>().c_str()) - 1] = 1;
			Data[i].tousen[atoi(jsonData["/tousen/2"_json_pointer].get<std::string>().c_str()) - 1] = 1;
			Data[i].tousen[atoi(jsonData["/tousen/3"_json_pointer].get<std::string>().c_str()) - 1] = 1;
			Data[i].tousen[atoi(jsonData["/tousen/4"_json_pointer].get<std::string>().c_str()) - 1] = 1;
			Data[i].tousen[atoi(jsonData["/tousen/5"_json_pointer].get<std::string>().c_str()) - 1] = 1;
			Data[i].tousen[atoi(jsonData["/tousen/6"_json_pointer].get<std::string>().c_str()) - 1] = 1;
			Data[i].tousen[43 + atoi(jsonData["/tousen/bonus_1"_json_pointer].get<std::string>().c_str()) - 1] = 1;
		}
	}
}