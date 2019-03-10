#pragma once
#include "DataSet.h"
#include "Data.h"
#include <string>


class CIFAR_10 : public DataSet
{
private :
	void readImages(const std::string path_MNIST[]);
	void readSet(std::vector<std::vector<float>>& inputs,
	             std::vector<std::vector<float>>& labels, std::ifstream& file);
	void loadData() override;

public:
	CIFAR_10();
};
