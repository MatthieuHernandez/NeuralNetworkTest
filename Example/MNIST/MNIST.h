#ifndef MNIST_H
#define MNIST_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <iomanip>

#include "Header FIles/Data.h"

class MNIST : public Data
{
private :
    void readImages(const std::string path_MNIST[]);
	static void readSet(Set &set, std::ifstream &images, std::ifstream &labels);
	MNIST();
	void loadData() override;
};

template <typename T>
std::string to_string_with_precision(const T value, const int n = 3)
{
	ostringstream out;
	out << fixed << std::setprecision(n) << value;
	return out.str();
}

#endif // MNIST_H
