#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <string>
#include <cstdlib>
#include "activationFunction.h"

static int randomBetween(const int a, const int b)  // WARNING TO : b excluded
{
    return rand()%(b-a)+a;
}

class Perceptron
{
    private :

        std::vector<float> weights;
        std::vector<float> previousDeltaWeights;
        std::vector<float> lastInputs;
        std::vector<float> errors;

		float lastOutput;

        int numberOfInputs;

        float learningRate;
        float momentum;
        float bias;

        std::unique_ptr<ActivationFunction> activationFunction;

        float randomInitializeWeight() const;
        

    public :

        Perceptron(int numberOfInputs, activationFunctionType activationFunction, float learningRate, float momentum);

        std::vector<float>& backOutput(float error);
        float output(const std::vector<float> &inputs);
		void train(const std::vector<float> &inputs, float error);

        void addAWeight();
        int isValid();
        std::string display();

        std::vector<float> getWeights() const;
        void setWeights(const std::vector<float> &weights);

        float getWeight(int w) const;
        void setWeight(int w, float weight);

        float getBias() const;
        void setBias(float bias);

        int getNumberOfInputs() const;

		void operator=(const Perceptron &perceptron);
        bool operator==(const Perceptron &perceptron) const;
        bool operator!=(const Perceptron &perceptron) const;
};
#endif // PERCEPTRON_H
