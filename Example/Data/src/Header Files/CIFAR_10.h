#pragma once
#include "DataSet.h"
#include "Data.h"
#include <string>


class CIFAR_10 : public DataSet
{
private :
	void readImages(const std::string path_MNIST[]);
	void readSet(const snn::set set, std::ifstream& file);
	void loadData() override;

public:
	CIFAR_10();
};
