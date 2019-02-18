#pragma once
#include "activationFunction.h"
#include <limits>

class Sigmoid : public ActivationFunction
{
private :

	activationFunctionType getType() const override { return sigmoid; }


public:

	float function(const float x) const override
	{
		float result = 1.0f / (1.0f + exp(-x));
		if (result != result)
		{
			if (x > 0)
				return 1;
			return 0;
		}
		return result;
	}

	float derivative(const float x) const override
	{
		float result = exp(-0) / pow((exp(-0) + 1.0f), 2);
		if (result != result)
			return exp(-0) / pow((exp(-0) + 1.0f), 2);
		return result;
	}
};
