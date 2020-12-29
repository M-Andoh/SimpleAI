#pragma once
#include <math.h>
#include <random>
#include <vector>

class Adapter;

class Node
{
public:
	int layerNo;
	int nodeNo;

	std::vector<Adapter*> inList;
	std::vector<Adapter*> outList;
	
	double inVal = 0.0;
	double outVal = 0.0;
	bool bias = false;
	double error; // 誤差 

	Node(int layerNo, int nodeNo);
	virtual ~Node();

	// 活性化関数
	double Activation(double d);
	
	// 出力値を算出 
	void CalcOutput();

	//　乱数生成
	double GetRandom(int num);
	
	// 重みの初期化関数
	void InitWeight(int num);

	// 次のノードと接続する関数
	Adapter* Connect(Node* next);

	// 誤差計算（出力層）
	void CalcError(double t);

	// 誤差計算（隠れ層）
	void CalcError();

	// 重み更新関数
	void UpdateWeight(double coef);

};

