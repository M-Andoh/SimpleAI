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

// ��������
double Node::GetRandom(int num) {
	static std::random_device seed_gen;
	//std::mt19937 engine;
	//engine.seed(seed_gen());
	//std::normal_distribution<> dist(0.0, 1.0);       // ����0, ���U�l1.0�̐��K���z
	//return dist(engine);
	unsigned int max_value = std::random_device::max();
	double max = max_value;
	double a = (double)seed_gen() / max;
	double b = (double)seed_gen() / max;
	double r = sqrt(-2.0 * log(a)) * sin(2.0 * M_PI * b) * 0.1;
	//r = 0.5;
	return r;
}

// �������֐�
double Node::Activation(double d) {
	return (1.0 / (1.0 + exp(-d)));
}

// �������֐������
double DeActivation(double d) {
	return ((1.0 - d) * d);
}

// �o�͒l���Z�o 
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
// �d�݂̏������֐�
void Node::InitWeight(int num) {
	for (size_t i = 0; i < inList.size(); ++i) {
		inList[i]->weight = GetRandom(num);
	}
}

// ���̃m�[�h�Ɛڑ�����֐�
Adapter* Node::Connect(Node* next) {
	Adapter* adapter = new Adapter(this, next);
	next->inList.push_back(adapter);
	this->outList.push_back(adapter);
	return adapter;
}

// �덷�v�Z�i�o�͑w�j
void Node::CalcError(double t) {
	error = t - outVal; 
}

// �덷�v�Z�i�B��w�j
void Node::CalcError() {
	error = 0;
	for (size_t i = 0; i < outList.size(); ++i) {
		error += (outList[i]->weight * outList[i]->output->error);
	}
}

// �d�ݍX�V�֐�
void Node::UpdateWeight(double coef) {
	for (size_t i = 0; i < inList.size(); ++i) {
		inList[i]->weight += (coef * error * DeActivation(outVal) * inList[i]->input->outVal);
	}
}

