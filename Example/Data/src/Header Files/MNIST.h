#pragma once
#include "DataSet.h"
#include <string>
#include <iomanip>

#include <sstream>

// ReSharper disable once CppInconsistentNaming
class MNIST : public DataSet
{
private :
	void readImages(const std::string path_MNIST[]);
	void readSet(std::vector<std::vector<float>>& inputs,
	             std::vector<std::vector<float>>& labels,
	             std::ifstream& images,
	             std::ifstream& imageLabels);

public :
	MNIST();
	void loadData() override;
};

template <typename T>
std::string to_string_with_precision(const T value, const int n = 3)
{
	std::ostringstream out;
	out << std::fixed << std::setprecision(n) << value;
	return out.str();
}
