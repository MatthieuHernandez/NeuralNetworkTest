#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H
#include <vector>

enum activationFunctionType
{
	sigmoid = 0,
	iSigmoid,
	tanH,
	reLU,
	gaussian
};

class ActivationFunction
{
private :

	virtual activationFunctionType getType() const { throw std::exception(); }


public :

	static std::vector<ActivationFunction*> listOfActivationFunction;

	ActivationFunction() = default;
	virtual ~ActivationFunction() = default;
	static void initialize();
	static ActivationFunction* getActivationFunction(activationFunctionType type);

	virtual float function(const float) const { throw std::exception(); }
	virtual float derivate(const float) const { throw std::exception(); }

	void operator=(const ActivationFunction& activationFunction);
	bool operator==(const ActivationFunction& activationFunction) const;
	bool operator!=(const ActivationFunction& activationFunction) const;
};

#endif // ACTIVATIONFUNCTIONS_H
