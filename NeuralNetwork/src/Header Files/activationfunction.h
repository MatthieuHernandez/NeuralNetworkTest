#ifndef ACTIVATIONFUNCTIONS_H
#define ACTIVATIONFUNCTIONS_H

#include <cmath>
#include <vector>

enum activationFunction
{
	sigmoid = 0,
	tanH,
	reLU,
	gaussian,
	stdp
};

class ActivationFunction
{
public :

	static std::vector<ActivationFunction*> listOfActivationFunction;

	static void initialize();
	virtual ~ActivationFunction() = default;

	virtual float function(const float) const { throw std::exception(); }
	virtual float derivate(const float) const { throw std::exception(); }
};

class Sigmoid : public ActivationFunction
{
public:
	float function(const float x) const override { return 1.0f / (1.0f + exp(-x)); }
	float derivate(const float x) const override { return x * (1.0f - x); }
	// * x stdp // x*exp(-x) / pow((1.0f + exp(-x)), 2);
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

class STDP : public ActivationFunction
{
private :
	constexpr const static float a = 5; // 6
	constexpr const static float b = 1; // 2

public :
	float function(const float x) const override { return a * x * exp(-x * b) / pow((1.0f + exp(-x * b)), 2); }
	float derivate(const float x) const override { return -((a*exp(b*x)*((b*x-1)*exp(b*x)-(b*x)-1))/(pow(exp(b*x)+1, 3))); } // -((6*exp(2*x)*((2*x-1)*exp(2*x)-2*x-1))/(exp(2*x)+1)^3)
};

#endif // ACTIVATIONFUNCTIONS_H

//A * pa = &b;
//pa->F1(); // affiche "A::F1()"
//pa->F2(); // affiche "B::F2()" <-- grâce à virtual

//A & ra = b;
//ra.F1(); // affiche "A::F1()"
//ra.F2(); // affiche "B::F2()" <-- grâce à virtual
