#pragma once
#include "activationFunction.h"

class ImprovedSigmoid : public ActivationFunction
{
private :

	virtual activationFunctionType getType() const { return iSigmoid; }

public:

	float function(const float x) const override
	{
		return 1.0f / (1.0f + exp(-x)) + 0.05f * x;
	}

	float derivate(const float x) const override
	{
		return exp(-x) / pow((exp(-x) + 1.0f), 2) + 0.05f;
	}
};
