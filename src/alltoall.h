#ifndef ALLTOALL_H
#define ALLTOALL_H

#include "layer.h"
#include "perceptron.h"

class AllToAll : public Layer
{
    private :


    public :

        AllToAll(uint numberOfInputs, uint numberOfNeurons, ActivationFunction *function, float learningRate, float momentum);
        std::vector<float> output(std::vector<float> &inputs);
        std::vector<float> backOutput(std::vector<float> & inputError);

};

#endif // ALLTOALL_H
