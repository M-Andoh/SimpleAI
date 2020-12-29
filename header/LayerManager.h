#pragma once
#include <vector>
#include <fstream>
#include<iostream>
#include "Layer.h"

class LayerManager
{
public:
	int LayerCount;
	std::vector<Layer*> layerList;

	LayerManager();
	virtual ~LayerManager();

	// レイヤーの追加
	void AddLayer(int nodeNum);

	// 入力層にデータを設定し、出力層までの出力値を計算する
	void CalcOutput(double* input);

	// 最大値のIndex(認識 結果）を返す
	size_t GetMaxIndex();

	// 重みの初期化
	void InitWeight();
	
	// 重みの更新
	void UpdateWeight(double coef);

	// 誤差の計算
	void CalcError(double* train);
	
	// 重みをファイルに保存する
	void SaveWeight(const char* filename);
	void SaveWeight(std::string& filename);

	// ファイルから重みを読み込む
	void LoadWeight(const char* filename);
	void LoadWeight(std::string& filename);
};

