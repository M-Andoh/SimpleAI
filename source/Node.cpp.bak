#include <iostream>
#include <random>
#include <math.h>
#include "Node.h"
#include "Adapter.h"

Node::Node(int _layerNo = -1, int _nodeNo = -1) :
	layerNo(_layerNo), nodeNo(_nodeNo)
{
	// std::cout << "Node,constructor," << layerNo << "," << nodeNo << std::endl;
}

Node::~Node()
{
	std::vector<Adapter*> wkList = outList;
	for (size_t i = 0; i < wkList.size(); ++i) {
		delete wkList[i];
	}
	// std::cout << "Node,destructor," << layerNo<<"," << nodeNo << std::endl;
}

// 乱数生成
double Node::GetRandom(int num) {
	static std::random_device seed_gen;
	//std::mt19937 engine;
	//engine.seed(seed_gen());
	//std::normal_distribution<> dist(0.0, 1.0);       // 平均0, 分散値1.0の正規分布
	//return dist(engine);
	unsigned int max_value = std::random_device::max();
	double max = max_value;
	double a = (double)seed_gen() / max;
	double b = (double)seed_gen() / max;
	double r = sqrt(-2.0 * log(a)) * sin(2.0 * M_PI * b) * 0.1;
	//r = 0.5;
	return r;
}

// 活性化関数
double Node::Activation(double d) {
	return (1.0 / (1.0 + exp(-d)));
}

// 活性化関数を微分
double DeActivation(double d) {
	return ((1.0 - d) * d);
}

// 出力値を算出 
void Node::CalcOutput() {
	inVal = 0.0;

	if (inList.size() == 0) {
		return;
	}

	for (size_t i = 0; i < inList.size(); ++i) {
		inVal += inList[i]->GetOutput();
	}
	outVal = Activation(inVal);
}
// 重みの初期化関数
void Node::InitWeight(int num) {
	for (size_t i = 0; i < inList.size(); ++i) {
		inList[i]->weight = GetRandom(num);
	}
}

// 次のノードと接続する関数
Adapter* Node::Connect(Node* next) {
	Adapter* adapter = new Adapter(this, next);
	next->inList.push_back(adapter);
	this->outList.push_back(adapter);
	return adapter;
}

// 誤差計算（出力層）
void Node::CalcError(double t) {
	error = t - outVal; 
}

// 誤差計算（隠れ層）
void Node::CalcError() {
	error = 0;
	for (size_t i = 0; i < outList.size(); ++i) {
		error += (outList[i]->weight * outList[i]->output->error);
	}
}

// 重み更新関数
void Node::UpdateWeight(double coef) {
	for (size_t i = 0; i < inList.size(); ++i) {
		inList[i]->weight += (coef * error * DeActivation(outVal) * inList[i]->input->outVal);
	}
}

