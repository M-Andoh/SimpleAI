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
	double error; // �덷 

	Node(int layerNo, int nodeNo);
	virtual ~Node();

	// �������֐�
	double Activation(double d);
	
	// �o�͒l���Z�o 
	void CalcOutput();

	//�@��������
	double GetRandom(int num);
	
	// �d�݂̏������֐�
	void InitWeight(int num);

	// ���̃m�[�h�Ɛڑ�����֐�
	Adapter* Connect(Node* next);

	// �덷�v�Z�i�o�͑w�j
	void CalcError(double t);

	// �덷�v�Z�i�B��w�j
	void CalcError();

	// �d�ݍX�V�֐�
	void UpdateWeight(double coef);

};

