#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "activationFunction.h"
#include "alltoall.h"


class NeuralNetwork
{
    private :

        static bool isTheFirst;
        static void initialize();

        float maxOutputValue;
        int maxOutputIndex;

        int lastError;
        float learningRate;
        float clusteringRate;
        float previousClusteringRate;
        float error;
        float momentum;

        int numberOfResultsClassifiedWell;
        int numberOfResultsMisclassefied;

        int shortRunCounter;

        int numberOfHiddenLayers;
        int numberOfLayers;
        int numberOfInput;
        int numberOfOutputs;

        std::vector<int> structureOfNetwork;
		std::vector<activationFunctionType> activationFunctionByLayer;

        std::vector<std::unique_ptr<Layer>> layers;

        bool classifiedWell;

        std::vector<float> errors;
		std::vector<float> outputs;

        void backpropagationAlgorithm(const std::vector<float> &inputs, const std::vector<float> &desired);
		std::vector<float> calculateError(const std::vector<float> &inputs, const std::vector<float> &desired);

        void resetAllNeurons();


    public :

        NeuralNetwork(std::vector<int> structureOfNetwork,
                      std::vector<activationFunctionType> activationFunctionByLayer,
                      const float learningRate = 0.05f,
                      const float momentum = 0.0f);

		~NeuralNetwork() = default;

        void train(const std::vector<float> &inputs, const std::vector<float> &desired);
        std::vector<float> output(const std::vector<float>& inputs);

        void calculateClusteringRateForRegressionProblemWithPrecision(const std::vector<float>& inputs, const std::vector<float>& desired, float precision = 0.5f);
        void calculateClusteringRateForRegressionProblemSeparateByValue(const std::vector<float>& inputs, const std::vector<float>& desired, float separator = 0.0f);
        void calculateClusteringRateForClassificationProblem(const std::vector<float> &inputs, int classNumber);

        void addANeuron(int layerNumber);

        int isValid();
        int getLastError() const;

        void setLearningRate(float learningRate);
        float getLearningRate() const;
        void setMomentum(float value);
        float getMomentum() const;
        //void setNumberOfSameClusteringAfterReset(int number);
        //int getNumberOfSameClusteringAfterReset() const;
        //void setLenghtOfShortRuns(int lenght);

        //int getLenghtOfShortRuns() const;
        int getShortRunCounter() const;
        int getNumberOfInputs() const;
        int getNumberOfHiddenLayers() const;
        int getNumberOfNeuronsInLayer(int layerNumber) const;
		activationFunctionType getActivationFunctionInLayer(int layerNumber) const;
        int getNumberOfResultsClassifiedWell() const;
        int getNumberOfNegativeResultsMisclassefied() const;
        int getNumberOfOutputs() const;
        float getClusteringRate();

        bool operator==(const NeuralNetwork &neuralNetwork);
        bool operator!=(const NeuralNetwork &neuralNetwork);
};

class notImplementedException : public std::exception
{
public:
	notImplementedException() : std::exception("Function not yet implemented") { };
};

#endif // NEURAL_NETWORK_H
