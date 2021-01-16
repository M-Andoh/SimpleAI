#pragma once
#include <iostream>
#include <memory.h>

class Loto7 {
public:
	static const int dataNum = (43 * 2);
	static const int dataKaigou = (10);

	Loto7() : kaigou(0), tousen(new char[dataNum]) {
		memset(tousen, 0, sizeof(char[dataNum]));
		// for (int i = 0; i < dataNum; ++i) {
		// 	std::cerr << tousen[i] << " ";
		// }
		 //std::cerr << std::endl;
	}
	
	Loto7(const Loto7& loto6) : kaigou(loto6.kaigou), tousen(loto6.tousen) {
	}
	Loto7& operator=(const Loto7& loto6) {
		kaigou = loto6.kaigou;
		tousen = loto6.tousen;
		return *this;
	}

	Loto7(Loto7&& loto6) : kaigou(loto6.kaigou), tousen(loto6.tousen) {
		kaigou = loto6.kaigou;
		loto6.kaigou = 0;
		tousen = loto6.tousen;
		loto6.tousen = nullptr;
	}
	Loto7& operator=(Loto7&& loto6) {
		kaigou = loto6.kaigou;
		loto6.kaigou = 0;
		tousen = loto6.tousen;
		loto6.tousen = nullptr;
		return *this;
	}

	virtual ~Loto7() {}

	int kaigou;
	char* tousen;
};

