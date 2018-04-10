#ifndef DATA_H
#define DATA_H

class Data
{
private:

	unsigned int index{};
	void suffle();


protected :

	 int sizeOfData{}; // size of one data, equal to size of neural network inputs
	 int numberOfLabel{}; // the number of class, equal to size of neural network outputs

	struct Set²
	{
		const int size{};
		std::vector<std::vector<float>> data{};
		std::vector<std::vector<float>> labels{};
	} trainig, testing;


public:

	virtual ~Data() = default;
	virtual void loadData() = 0;
	void getNextData(bool isRandom = true);
};

#endif // DATA_H
