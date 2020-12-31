#include <stdlib.h>
#include <limits.h>
#include <sstream>
#include "LayerManager.h"
#include "Node.h"
#include "Adapter.h"


LayerManager::LayerManager() :
	LayerCount(0)
{
	// std::cout << "LayerManager,constructor" << std::endl;
}

LayerManager::~LayerManager() {
	for (size_t i = 0; i < layerList.size(); ++i) {
		delete layerList[i];
	}
	layerList.clear();
	// std::cout << "LayerManager,destructor" << std::endl;
}


// レイヤーの追加
void LayerManager::AddLayer(int nodeNum) {
	++LayerCount;
	Layer* layer = new Layer(nodeNum, (int)layerList.size() + 1);
	if (layerList.size() >= 1) {
		layerList[layerList.size() - 1]->ConnectLayer(layer);
	}
	layerList.push_back(layer);
}

// 入力層にデータを設定し、出力層までの出力値を計算する
void LayerManager::CalcOutput(double* input) {
	layerList[0]->SetInputData(input);
	for (size_t i = 0; i < layerList.size(); ++i) {
		layerList[i]->CalcOutput();
	}
}

// 最大値のIndex(認識 結果）を返す
size_t LayerManager::GetMaxIndex() {
	// 出力層の最大値をチェック
	Layer* layer = layerList[layerList.size() - 1];
	size_t maxIndex = 0;
	double maxVal = layer->nodeList[0]->outVal;
	for (size_t i = 1; i < layer->nodeList.size(); ++i) {
		if (layer->nodeList[i]->outVal > maxVal) {
			maxVal = layer->nodeList[i]->outVal;
			maxIndex = i;
		}
	}
	return maxIndex;
}

// 重みの初期化
void LayerManager::InitWeight() {
	for (size_t i = 0; i < layerList.size(); ++i) {
		layerList[i]->InitWeight();
	}
}

// 重みの更新
void LayerManager::UpdateWeight(double coef) {
	for (size_t i = 0; i < layerList.size(); ++i) {
		layerList[i]->UpdateWeight(coef);
	}
}

// 誤差の計算
void LayerManager::CalcError(double* train) {
	// 出力層ノードの誤差を計算
	std::vector<Node*>* list = &layerList[layerList.size() - 1]->nodeList;
	for (size_t i = 0; i < list->size(); ++i) {
		list->at(i)->CalcError(train[i]);
	}

	// 隠れ層の誤差を後ろから順次計算
	for (int i = (int)layerList.size() - 2; i >= 0; --i) {
		list = &layerList[i]->nodeList;
		for (size_t j = 0; j < list->size(); ++j) {
			list->at(j)->CalcError();
		}
	}
}

// 重みをファイルに保存する
void LayerManager::SaveWeight(const char* filename) {
	std::string str = filename;
	SaveWeight(str);
}

void LayerManager::SaveWeight(std::string& filename) {
	std::ofstream  sw;
	try {
		char buffer[PATH_MAX];
		char* fname = realpath(filename.c_str(), buffer);

		std::cerr << fname << std::endl;
		sw.open(filename);
		if (!sw) {
			std::cerr << "file open error : " << filename.c_str() << std::endl;
		}

		// 最初にレイヤーの数を書き込む 
		sw << LayerCount << std::endl;
		for (int i = 0; i < LayerCount; i++)
		{
			// ノードの数 
			sw << layerList[i]->nodeCount << std::endl;
			// ノードが持つAdapterの重みをカンマ区切りで書き込み 
			for (size_t ii = 0; ii < layerList[i]->nodeList.size(); ii++)
			{
				Node* node = layerList[i]->nodeList[ii];
				for (size_t iii = 0; iii < node->inList.size(); iii++)
				{
					sw << node->inList[iii]->weight << ',';
				}
				sw<<std::endl;
			}
		}
	}
	catch (std::exception ex) {

	}
}

// ファイルから重みを読み込む
void LayerManager::LoadWeight(const char* filename) {
	std::string str = filename;
	this->LoadWeight(str);
}

void LayerManager::LoadWeight(std::string& filename) {
	std::ifstream sr;
	try {
		char buffer[PATH_MAX];
		char* fname = realpath(filename.c_str(), buffer);

		std::cerr << fname << std::endl;
		sr.open(filename);
		if (!sr) {
			std::cerr << "file open error : " << filename << std::endl;
		}

		size_t layerNum;
		sr >> layerNum;
		for (size_t i = 0; i < layerList.size(); ++i) {
			delete layerList[i];
		}
		layerList.clear();

		for (size_t i = 0; i < layerNum; ++i) {
			int nodeNum;
			sr >> nodeNum;
			AddLayer(nodeNum);

			std::vector<Node*>& nodeList = layerList[layerList.size() - 1]->nodeList;
			for (size_t ii = 0; ii < nodeList.size(); ++ii) {
				// 重みの読み込み
				for (size_t iii = 0; iii < nodeList[ii]->inList.size(); ++iii) {
					double weight;
					char separator;
					sr >> weight >> separator;
					nodeList[ii]->inList[iii]->weight = weight;
				}
			}
		}
	}
	catch (std::exception ex) {

	}
}

