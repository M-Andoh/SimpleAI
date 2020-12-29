#pragma once

class Node;

class Adapter
{
	int inLayerNo;
	int inNodeNo;
	int outLayerNo;
	int outNodeNo;

public:
	Node* input;
	Node* output;
	double weight;

	Adapter(Node* _input, Node* _output);
	virtual ~Adapter();

	double GetOutput();
};
