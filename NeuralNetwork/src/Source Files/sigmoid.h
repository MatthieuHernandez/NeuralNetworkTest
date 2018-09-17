#pragma once
#include "activationFunction.h"

class Sigmoid : public ActivationFunction
{
private :

	activationFunctionType getType() const override { return sigmoid; }


public:

	float function(const float x) const override
	{
		auto a = 1.0f / (1.0f + exp(-x));
		return a;
	}

	float derivate(const float x) const override
	{
		auto b =  exp(-x) / pow((exp(-x) + 1.0f), 2);
		return b;
	}
};
