#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "activationfunction.h"
#include "alltoall.h"

class NeuralNetwork
{
    private :

        static bool isTheFirst;
        static void initialize();

        float maxOutputValue{};
        uint maxOutputIndex{};

        uint lastError;
        float learningRate;
        float clusteringRate;
        float previousClusteringRate{};
        float error;
        float momentum;

        uint numberOfResultsClassifiedWell;
        uint numberOfResultsMisclassefied;

        int lenghtOfShortRuns;
        int shortRunCounter;

        uint numberOfHiddenLayers;
        uint numberOfLayers;
        uint numberOfInput;
        uint numberOfOutput;

        std::vector<uint> structureOfNetwork;
        std::vector<Layer> layers;

        bool classifiedWell{};

        std::vector<std::vector<float>> results;
        std::vector<std::vector<float>> errors;
        std::vector<float> outputs;

        void backpropagationAlgorithm(const std::vector<float> &inputs, const std::vector<float> &desired);

        void resetAllNeurons();


    public :

        NeuralNetwork();
        NeuralNetwork(std::vector<uint> structureOfNetwork,
                      std::vector<activationFunction> &activationFunctionByLayer,
                      float learningRate = 0.05f,
                      float momentum = 0.0f);

        void train(const std::vector<float> &inputs, const std::vector<float> &desired);
        std::vector<float> calculateOutput(const std::vector<float> &inputs);

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

        uint getLenghtOfShortRuns() const;
        uint getShortRunCounter() const;
        uint getNumberOfInputs() const;
        uint getNumberOfHiddenLayers() const;
        uint getNumberOfNeuronsInHiddenLayers(int layerNumber) const;
        uint getNumberOfResultsClassifiedWell() const;
        uint getNumberOfNegativeResultsMisclassefied() const;
        uint getNumberOfOutputs() const;
        float getClusteringRate();

        bool operator==(const NeuralNetwork &neuralNetwork);
        bool operator!=(const NeuralNetwork &neuralNetwork);
};

#endif // NEURAL_NETWORK_H
