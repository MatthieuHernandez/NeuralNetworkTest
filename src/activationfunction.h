#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include <cmath>
#include <vector>


enum activationFunction
{
	sigmoid = 0,
	tanH,
	reLU,
	gaussian
};

class ActivationFunction
{
public :

	static std::vector<ActivationFunction*> listOfActivationFunction;

	static void initialize();

	~ActivationFunction() = default;
	virtual float function(const float x) const { return NAN; }
	virtual float derivate(const float x) const { return NAN; }
};

class Sigmoid : public ActivationFunction
{
public:
	float function(const float x) const override { return 1.0 / (1.0 + exp(-x)); }
	float derivate(const float x) const override { return exp(-x) / pow((1 + exp(-x)), 2); } // * x stdp
};

class TanH : public ActivationFunction
{
public:
	float function(const float x) const override { return tanh(x); }
	float derivate(const float x) const override { return 1 - (pow(tanh(x), 2)); }
};

class ReLU : public ActivationFunction // WARNING : bad function, if sum < 0 at start, neuron will never learn
{
public :
	float function(const float x) const override { return (x > 0.0f) ? 0.0f : x; }
	float derivate(const float x) const override { return (x > 0.0f) ? 0.0f : 1.0f; }
};

class Gaussian : public ActivationFunction
{
public :
	float function(const float x) const override { return exp(-pow(x, 2)); }
	float derivate(const float x) const override { return -2 * x * exp(-pow(x, 2)); }
};


#endif // ACTIVATIONFUNCTIONS_H


//A * pa = &b;
//pa->F1(); // affiche "A::F1()"
//pa->F2(); // affiche "B::F2()" <-- grâce à virtual

//A & ra = b;
//ra.F1(); // affiche "A::F1()"
//ra.F2(); // affiche "B::F2()" <-- grâce à virtual
