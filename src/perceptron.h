#ifndef PERCEPTRON_H
#define PERCEPTRON_H

#include <vector>
#include <string>
#include <cstdlib>
#include "activationfunction.h"

typedef unsigned int uint;

static int randomBetween(const int a, const int b)  // WARNING TO : b excluded
{
    return rand()%(b-a)+a;
}

class Perceptron
{
    private :

        std::vector<float> weights;
        std::vector<float> deltaWeights;
        std::vector<float> previousDeltaWeights;
        std::vector<float> lastInputs;
        std::vector<float> errors;

        uint numberOfInputs;

        float learningRate;
        float momentum;
        float bias;

        ActivationFunction *activationFunction;

        float randomInitializeWeight() const;
        

    public :

        Perceptron(uint numberOfInputs, ActivationFunction *activationFunction, float learningRate, float momentum);

        std::vector<float>& backOutput(float error);
        float output(const std::vector<float> &inputs);
		void train(const std::vector<float> &inputs, float error);

        void addAWeight();
        uint isValid();
        std::string display();

        std::vector<float> getWeights() const;
        void setWeights(const std::vector<float> &weights);

        float getWeight(uint i) const;
        void setWeight(uint i, float weight);

        float getBias() const;
        void setBias(float bias);

        uint getNumberOfInputs() const;

        bool operator==(const Perceptron &perceptron);
        bool operator!=(const Perceptron &perceptron);
};
#endif // PERCEPTRON_H
