#ifndef DATA_H
#define DATA_H
#include <vector>
#include <memory>


enum set
{
	testing = 0,
	training
};

enum problemType
{
	classification = 0,
	regression
};

class Data
{
protected:
	std::vector<int> indexes;

	void clearData();

public:

	void shuffle();
	void unshuffle();

	int sizeOfData{}; // size of one data, equal to size of neural network inputs
	int numberOfLabel{}; // the number of class, equal to size of neural network outputs

	problemType problem;

	struct Set
	{
		unsigned int index{0};
		unsigned int size{0}; // number of data inside set
		std::vector<std::vector<float>> data{};
		std::vector<std::vector<float>> labels{};
	} sets[2];

	virtual ~Data() = default;
	virtual void loadData() = 0;

	virtual std::vector<float>& getTrainingData(const int index);
	virtual std::vector<float>& getTestingData(const int index);

	virtual int getLabel(const int, set) { throw std::exception(); }
	virtual int getTrainingLabel(const int) { throw std::exception(); }
	virtual int getTestingLabel(const int) { throw std::exception(); }

	virtual std::vector<float>& getTrainingOutputs(const int index);
	virtual std::vector<float>& getTestingOutputs(const int) { throw std::exception(); }
};


#endif // DATA_H
