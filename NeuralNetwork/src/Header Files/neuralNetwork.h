#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "activationfunction.h"
#include "alltoall.h"
#include <memory>

class NeuralNetwork
{
    private :

        static bool isTheFirst;
        static void initialize();

        float maxOutputValue;
        uint maxOutputIndex;

        uint lastError;
        float learningRate;
        float clusteringRate;
        float previousClusteringRate;
        float error;
        float momentum;

        uint numberOfResultsClassifiedWell;
        uint numberOfResultsMisclassefied;

        int shortRunCounter;

        uint numberOfHiddenLayers;
        uint numberOfLayers;
        uint numberOfInput;
        uint numberOfOutputs;

        std::vector<uint> structureOfNetwork;
		std::vector<activationFunction> activationFunctionByLayer;

        std::vector<std::unique_ptr<Layer>> layers;

        bool classifiedWell;

        std::vector<float> errors;
		std::vector<float> outputs;

        void backpropagationAlgorithm(const std::vector<float> &inputs, const std::vector<float> &desired);
		std::vector<float> calculateError(const std::vector<float> &inputs, const std::vector<float> &desired);

        void resetAllNeurons();


    public :

        NeuralNetwork(std::vector<unsigned int>& structureOfNetwork,
                      std::vector<activationFunction>& activationFunctionByLayer,
                      const float learningRate = 0.05f,
                      const float momentum = 0.0f);

        void train(const std::vector<float> &inputs, const std::vector<float> &desired);
        std::vector<float> output(const std::vector<float>& inputs);

        void calculateClusteringRateForRegressionProblem(const std::vector<float> &inputs, const std::vector<int> &desired);
        void calculateClusteringRateForClassificationProblem(const std::vector<float> &inputs, const uint classNumber);

        void addANeuron(uint layerNumber);

        int isValid();
        int getLastError() const;

        void setLearningRate(float learningRate);
        float getLearningRate() const;
        void setMomentum(float value);
        float getMomentum() const;
        //void setNumberOfSameClusteringAfterReset(uint number);
        //int getNumberOfSameClusteringAfterReset() const;
        void setLenghtOfShortRuns(uint lenght);

        int getLenghtOfShortRuns() const;
        int getShortRunCounter() const;
        int getNumberOfInputs() const;
        int getNumberOfHiddenLayers() const;
        int getNumberOfNeuronsInLayer(int layerNumber) const;
		activationFunction getActivationFunctionInLayer(int layerNumber) const;
        int getNumberOfResultsClassifiedWell() const;
        int getNumberOfNegativeResultsMisclassefied() const;
        int getNumberOfOutputs() const;
        float getClusteringRate();

        bool operator==(const NeuralNetwork &neuralNetwork);
        bool operator!=(const NeuralNetwork &neuralNetwork);
};

#endif // NEURAL_NETWORK_H
