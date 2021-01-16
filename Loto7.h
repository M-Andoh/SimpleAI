#pragma once
#include <iostream>
#include <memory.h>

class Loto7 {
public:
	static const int dataNum = (37 * 2);
	static const int dataKaigou = (10);

	Loto7() : kaigou(0), tousen(new char[dataNum]) {
		memset(tousen, 0, sizeof(char[dataNum]));
		// for (int i = 0; i < dataNum; ++i) {
		// 	std::cerr << tousen[i] << " ";
		// }
		 //std::cerr << std::endl;
	}
	
	Loto7(const Loto7& loto7) : kaigou(loto7.kaigou), tousen(loto7.tousen) {
	}
	Loto7& operator=(const Loto7& loto7) {
		kaigou = loto7.kaigou;
		tousen = loto7.tousen;
		return *this;
	}

	Loto7(Loto7&& loto7) : kaigou(loto7.kaigou), tousen(loto7.tousen) {
		kaigou = loto7.kaigou;
		loto7.kaigou = 0;
		tousen = loto7.tousen;
		loto7.tousen = nullptr;
	}
	Loto7& operator=(Loto7&& loto7) {
		kaigou = loto7.kaigou;
		loto7.kaigou = 0;
		tousen = loto7.tousen;
		loto7.tousen = nullptr;
		return *this;
	}

	virtual ~Loto7() {}

	int kaigou;
	char* tousen;
};

