#include <iostream>
#include "Layer.h"
#include "Activation.h"

Layer::Layer(int _count, Activation* _activation, int _layerNo) :
	layerNo(_layerNo), nodeCount(_count), activation(_activation->name)
{
	for (int i = 0; i < _count; ++i) {
		nodeList.push_back(new Node(_activation, layerNo, i + 1));
	}
	// std::cout << "Layer,constructor," << layerNo << std::endl;
}

Layer::~Layer(){
	for (size_t i = 0; i < nodeList.size(); ++i) {
		delete nodeList[i];
	}
	nodeList.clear();
	// std::cout << "Layer,destructor," << layerNo << std::endl;
}

// 出力値を計算 
void Layer::CalcOutput() {
	for (size_t i = 0; i < nodeList.size(); ++i) {
		nodeList[i]->CalcOutput();
	}
}

// 重みの初期化
void Layer::InitWeight() {
	for (size_t i = 0; i < nodeList.size(); ++i) {
		nodeList[i]->InitWeight((int)nodeList.size());
	}
}

// レイヤー間でNodeを全結合する
void Layer::ConnectLayer(Layer* next, Activation* activation) {
	// Node* biasNode = new Node(layerNo, nodeCount + 1);
	Node* biasNode = new Node(activation, layerNo, -1);
	biasNode->inVal = 1.0;
	biasNode->outVal = 1.0;
	biasNode->bias = true;
	nodeList.push_back(biasNode);

	for (size_t i = 0; i < nodeList.size(); ++i) {
		for (size_t j = 0; j < next->nodeList.size(); ++j) {
			nodeList[i]->Connect(next->nodeList[j]);
		}
	}
}

// 重みの更新
void Layer::UpdateWeight(double coef) {
	for (size_t i = 0; i < nodeList.size(); ++i) {
		nodeList[i]->UpdateWeight(coef);
	}
}

// Nodeにデータを設定
void Layer::SetInputData(double* data) {
	for (int i = 0; i < nodeCount; ++i) {
		nodeList[i]->outVal = data[i];
	}
}


