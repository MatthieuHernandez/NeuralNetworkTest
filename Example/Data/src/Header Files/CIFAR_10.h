#pragma once
#include "DataForClassification.h"

class CIFAR_10 : public DataForClassification
{
private :
	void readImages(const std::string path_MNIST[]);
	void readSet(const set set, std::ifstream& file);
	void loadData() override;

public:
	CIFAR_10();
};