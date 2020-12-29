#include <iostream>
#include "Adapter.h"
#include "Node.h"

Adapter::Adapter(Node* _input, Node* _output) :
	inLayerNo(_input->layerNo), inNodeNo(_input->nodeNo),
	outLayerNo(_output->layerNo), outNodeNo(_output->nodeNo),
	input(_input), output(_output)
{
	// std::cout << "Adapter,constructor" 
	//	<< "," << inLayerNo << "," << inNodeNo
	//	<< "," << outLayerNo << "," << outNodeNo
	//	<< std::endl;
}

Adapter::~Adapter(){
	std::vector<Adapter*>::iterator it;
	for (it = input->outList.begin();
		it != input->outList.end();
		++it)
	{
		if (this == *it) {
			input->outList.erase(it);
			break;
		}
	}

	for (it = output->inList.begin();
		it != output->inList.end();
		++it)
	{
		if (this == *it) {
			output->inList.erase(it);
			break;
		}
	}
	// std::cout << "Adapter,destructor"
	// 	<< "," << inLayerNo << "," << inNodeNo
	// 	<< "," << outLayerNo << "," << outNodeNo
	// 	<< std::endl;
}

double Adapter::GetOutput() {
	return input->outVal * weight;
}