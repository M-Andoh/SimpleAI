#pragma once
#include <vector>
#include "Node.h"

class Layer
{
public:
	int layerNo;
	int nodeCount;

	std::vector<Node*> nodeList;

	Layer(int count, int layerNo=-1);
	virtual ~Layer();

	// 出力値を計算 
	void CalcOutput();

	// 重みの初期化
	void InitWeight();

	// レイヤー間でNodeを全結合する
	void ConnectLayer(Layer* next);

	// 重みの更新
	void UpdateWeight(double coef);

	// Nodeにデータを設定
	void SetInputData(double* data);

};

