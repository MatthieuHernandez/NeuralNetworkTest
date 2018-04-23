#ifndef DATA_H
#define DATA_H

class Data
{
protected :

	enum set
	{
		testing = 0,
		training = 1
	};

	int sizeOfData{}; // size of one data, equal to size of neural network inputs
	int numberOfLabel{}; // the number of class, equal to size of neural network outputs


private:

	void shuffle();
	std::vector<float>& getNextData(set set, bool isRandom);
	std::vector<float>& getNextLabel(set set);


protected :

	struct Set
	{
		unsigned int index{0};
		unsigned int size{0};
		std::vector<std::vector<float>> data{};
		std::vector<std::vector<float>> labels{};
	} sets[2];


public:

	virtual ~Data() = default;
	virtual void loadData() = 0;

	std::vector<float>& getNextTrainingData(bool isRandom = true);
	std::vector<float>& getNextTrainingLabel();

	std::vector<float>& getNextTestingData();
	std::vector<float>& getNextTestingLabel();
};

#endif // DATA_H
