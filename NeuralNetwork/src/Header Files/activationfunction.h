#pragma once

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
public :

	//static std::vector<ActivationFunction*> listOfActivationFunction;

	ActivationFunction() = default;
	ActivationFunction(const ActivationFunction& activationFunction);
	virtual ~ActivationFunction() = default;
	static void initialize();
	static ActivationFunction* create(activationFunctionType type);

	virtual float function(const float) const = 0;
	virtual float derivate(const float) const = 0;

	virtual activationFunctionType getType() const = 0;

	virtual bool operator==(const ActivationFunction& activationFunction) const;
	virtual bool operator!=(const ActivationFunction& activationFunction) const;
};
