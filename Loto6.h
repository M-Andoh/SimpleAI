#pragma once
#include <iostream>
#include <memory.h>

class Loto6 {
public:
	static const int dataNum = (43 * 2);
	static const int dataKaigou = (10);

	Loto6() : kaigou(0), tousen(new char[dataNum]) {
		memset(tousen, 0, sizeof(char[dataNum]));
		// for (int i = 0; i < dataNum; ++i) {
		// 	std::cerr << tousen[i] << " ";
		// }
		 //std::cerr << std::endl;
	}
	
	Loto6(const Loto6& loto6) : kaigou(loto6.kaigou), tousen(loto6.tousen) {
	}
	Loto6& operator=(const Loto6& loto6) {
		kaigou = loto6.kaigou;
		tousen = loto6.tousen;
		return *this;
	}

	Loto6(Loto6&& loto6) : kaigou(loto6.kaigou), tousen(loto6.tousen) {
		kaigou = loto6.kaigou;
		loto6.kaigou = 0;
		tousen = loto6.tousen;
		loto6.tousen = nullptr;
	}
	Loto6& operator=(Loto6&& loto6) {
		kaigou = loto6.kaigou;
		loto6.kaigou = 0;
		tousen = loto6.tousen;
		loto6.tousen = nullptr;
		return *this;
	}

	virtual ~Loto6() {}

	int kaigou;
	char* tousen;
};

