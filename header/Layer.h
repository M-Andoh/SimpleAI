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

	// �o�͒l���v�Z 
	void CalcOutput();

	// �d�݂̏�����
	void InitWeight();

	// ���C���[�Ԃ�Node��S��������
	void ConnectLayer(Layer* next);

	// �d�݂̍X�V
	void UpdateWeight(double coef);

	// Node�Ƀf�[�^��ݒ�
	void SetInputData(double* data);

};

