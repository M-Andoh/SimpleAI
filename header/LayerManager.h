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

	// ���C���[�̒ǉ�
	void AddLayer(int nodeNum);

	// ���͑w�Ƀf�[�^��ݒ肵�A�o�͑w�܂ł̏o�͒l���v�Z����
	void CalcOutput(double* input);

	// �ő�l��Index(�F�� ���ʁj��Ԃ�
	size_t GetMaxIndex();

	// �d�݂̏�����
	void InitWeight();
	
	// �d�݂̍X�V
	void UpdateWeight(double coef);

	// �덷�̌v�Z
	void CalcError(double* train);
	
	// �d�݂��t�@�C���ɕۑ�����
	void SaveWeight(const char* filename);
	void SaveWeight(std::string& filename);

	// �t�@�C������d�݂�ǂݍ���
	void LoadWeight(const char* filename);
	void LoadWeight(std::string& filename);
};

