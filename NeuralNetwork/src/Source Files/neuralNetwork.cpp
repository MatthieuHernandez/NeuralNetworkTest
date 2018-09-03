#include "NeuralNetwork.h"
#include <ctime>
#include <algorithm>
#include <omp.h>

using namespace std;

bool NeuralNetwork::isTheFirst = true;

void NeuralNetwork::initialize()
{
	srand(static_cast<int>(time(nullptr)));
	rand();
	ActivationFunction::initialize();

	const auto numberOfCore = omp_get_num_procs();
	//omp_set_num_threads(numberOfCore * 2);
	//omp_set_num_threads(128);

	isTheFirst = false;
}

NeuralNetwork::NeuralNetwork(const std::vector<int> structureOfNetwork,
                             const std::vector<activationFunctionType> activationFunctionByLayer,
                             const float learningRate,
                             const float momentum)
{
	if (isTheFirst)
		this->initialize();

	this->structureOfNetwork = structureOfNetwork;
	this->activationFunctionByLayer = activationFunctionByLayer;
	this->learningRate = learningRate;
	this->shortRunCounter = 0;
	this->numberOfResultsClassifiedWell = 0;
	this->numberOfResultsMisclassefied = 0;
	this->clusteringRate = -1;

	this->numberOfLayers = static_cast<int>(structureOfNetwork.size()) - 1;
	this->numberOfHiddenLayers = static_cast<int>(structureOfNetwork.size()) - 2;
	this->numberOfInput = structureOfNetwork[0];
	this->numberOfOutputs = structureOfNetwork.back();

	this->momentum = 0;
	this->lastError = 0;
	this->error = 0;

	errors.resize(numberOfOutputs);
	outputs.resize(numberOfOutputs);

	layers.reserve(numberOfLayers);
	for (int l = 1; l < structureOfNetwork.size(); ++l)
	{
		unique_ptr<Layer> layer(new AllToAll(structureOfNetwork[l - 1],
		                                     structureOfNetwork[l],
		                                     this->activationFunctionByLayer[l - 1],
		                                     learningRate,
		                                     momentum));
		layers.push_back(move(layer));
	}
}

vector<float> NeuralNetwork::output(const vector<float>& inputs)
{
	this->outputs = layers[0]->output(inputs);

	for (int l = 1; l < numberOfLayers; ++l)
	{
		outputs = layers[l]->output(outputs);
	}
	return outputs;
}

void NeuralNetwork::calculateClusteringRateForRegressionProblemWithPrecision(
	const vector<float>& inputs, const vector<float>& desired, float precision)
{
	this->outputs = this->output(inputs);
	bool classifiedWell = true;
	for (int n = 0; n < numberOfOutputs; ++n)
	{
		if (this->outputs[n] > desired[n] + precision
			&& this->outputs[n] < desired[n] - precision)
		{
			classifiedWell = false;
			break;
		}
	}
	if (classifiedWell)
		numberOfResultsClassifiedWell++;
	else
		numberOfResultsMisclassefied++;
}

void NeuralNetwork::calculateClusteringRateForRegressionProblemSeparateByValue(
	const vector<float>& inputs, const vector<float>& desired, float separator)
{
	this->outputs = this->output(inputs);
	bool classifiedWell = true;
	for (int n = 0; n < numberOfOutputs; ++n)
	{
		if ((this->outputs[n] >= separator && desired[n] < separator
			|| this->outputs[n] <= separator && desired[n] > separator))
		{
			classifiedWell = false;
			break;
		}
	}
	if (classifiedWell)
		numberOfResultsClassifiedWell++;
	else
		numberOfResultsMisclassefied++;
}

void NeuralNetwork::calculateClusteringRateForClassificationProblem(const vector<float>& inputs, const int classNumber)
{
	maxOutputValue = -1;
	this->outputs = this->output(inputs);
	for (int n = 0; n < this->outputs.size(); ++n)
	{
		if (maxOutputValue < this->outputs[n])
		{
			maxOutputValue = this->outputs[n];
			maxOutputIndex = n;
		}
	}
	if (maxOutputIndex == classNumber)
		numberOfResultsClassifiedWell++;
	else
		numberOfResultsMisclassefied++;
}

void NeuralNetwork::train(const vector<float>& inputs, const vector<float>& desired)
{
	backpropagationAlgorithm(inputs, desired);
}

void NeuralNetwork::backpropagationAlgorithm(const vector<float>& inputs, const vector<float>& desired)
{
	this->outputs = this->output(inputs);
	auto errors = calculateError(this->outputs, desired);

	for (int l = numberOfLayers - 1; l > 0; --l)
	{
		errors = layers[l]->backOutput(errors);
	}
	layers[0]->train(errors);
}

inline vector<float> NeuralNetwork::calculateError(const vector<float>& outputs, const vector<float>& desired)
{
	for (int n = 0; n < numberOfOutputs; ++n)
	{
		if (desired[n] != -1.0f)
		{
			float e = desired[n] - outputs[n];
			this->errors[n] = e * abs(e);
		}
		else
			this->errors[n] = 0;
	}
	return this->errors;
}

void NeuralNetwork::resetAllNeurons()
{
	// TODO: rework function resetAllNeurons
	throw notImplementedException();
	/*for(int i = 0; i < neurons.size(); i++)
	{
	    for(int j = 0; j < neurons[i].size(); j++)
	    {
	        neurons[i][j] = Perceptron(neurons[i][j].getNumberOfInputs(), neurons[i][j].getLayerNumber(), neurons[i][j].getNumberInLayer());
	    }
	}*/
}

void NeuralNetwork::addANeuron(int)
{
	// TODO: rework function addANeuron
	throw notImplementedException();
	/*results[layerNumber].push_back(0);
	errors[layerNumber].push_back(0);
	outputs.push_back(0);

	if(layerNumber == 0)
	{
	    numberOfInput ++;
	    neurons[layerNumber].push_back(Perceptron(neurons[layerNumber][0].getWeights().size(), layerNumber, numberOfInput-1));
	    for(int i = 0; i < neurons[layerNumber+1].size(); i++)
	    {
	        neurons[layerNumber+1][i].addAWeight();
	    }

	}
	else if(layerNumber == numberOfHiddenLayers)
	{
	    numberOfOutputs ++;
	    neurons[layerNumber].push_back(Perceptron(neurons[layerNumber][0].getWeights().size(), layerNumber, numberOfOutputs-1));

	}
	else if(layerNumber > 0 && layerNumber < numberOfHiddenLayers)
	{
	    //numberOfNeuronsInHiddenLayers ++;
	    this->structureOfNetwork[layerNumber+1] ++;
	    for(int j = 1;  j < numberOfHiddenLayers; j++) // output neuron
	    {
	        neurons[j].push_back(Perceptron(neurons[j][0].getWeights().size(), functfqqsdfzsdef);

	        for(int i = 0; i < neurons[j+1].size(); i++)
	        {
	            neurons[j+1][i].addAWeight();
	        }
	    }
	}
	else
	{
	    lastError = 8;
	}*/
}

int NeuralNetwork::isValid()
{
	//TODO: rework isValid
	throw notImplementedException();
	/*int numberOfWeightsReal = 0;
	int computedNumberWeights = 0;

	for(int i = 0; i < neurons.size(); i++)
	{
	    if(((int)neurons[i].size() !=  structureOfNetwork[i+1] && i < numberOfHiddenLayers)
	    || ((int)neurons[i].size() != numberOfOutputs && i == numberOfHiddenLayers))
	    {
	        lastError = 10;
	        return lastError;
	    }
	}
	for(int i = 0; i < neurons.size(); i++)
	{
	    for(int j = 0; j < neurons[i].size(); j++)
	    {
	       numberOfWeightsReal += neurons[i][j].getNumberOfInputs();
	    }
	}

	for(int i=1; i<structureOfNetwork.size();i++)
	{
	    computedNumberWeights += structureOfNetwork[i-1] * structureOfNetwork[i];
	}

	if(numberOfWeightsReal != computedNumberWeights)
	{
	    lastError = 11;
	    cout << numberOfWeightsReal << endl;
	    cout << computedNumberWeights << endl;
	    return lastError;
	}
	if(numberOfInput < 1 || numberOfInput > 2073600) // 1920 * 1080
	{
	    lastError = 1;
	    return lastError;
	}
	if(numberOfHiddenLayers < 1 || numberOfHiddenLayers > 100)
	{
	    lastError = 2;
	    cout << numberOfHiddenLayers << endl;
	    return lastError;
	}
	if(neurons.size() != (unsigned)(numberOfHiddenLayers+1))
	{
	   lastError = 3;
	   return lastError;
	}
	if(learningRate < 0 || learningRate > 1 )
	{
	    return 5;
	    cout << learningRate << endl;
	}
	for(int i = 0; i < neurons.size(); i++)
	{
	    for(int j = 0; j < neurons[i].size(); j++)
	    {
	        if(neurons[i][j].isValid() != 0)
	        {
	          lastError = neurons[i][j].isValid();
	          return lastError;
	        }
	    }
	}
	return 0;*/
}

int NeuralNetwork::getLastError() const
{
	return lastError;
}

void NeuralNetwork::operator=(const NeuralNetwork& neuralNetwork)
{
	this->maxOutputIndex = neuralNetwork.maxOutputIndex;
	this->lastError = neuralNetwork.lastError;
	this->learningRate = neuralNetwork.learningRate;
	this->clusteringRate = neuralNetwork.clusteringRate;
	this->previousClusteringRate = neuralNetwork.previousClusteringRate;
	this->error = neuralNetwork.error;
	this->momentum = neuralNetwork.momentum;
	this->numberOfResultsClassifiedWell = neuralNetwork.numberOfResultsClassifiedWell;
	this->numberOfResultsMisclassefied = neuralNetwork.numberOfResultsMisclassefied;
	this->numberOfHiddenLayers = neuralNetwork.numberOfHiddenLayers;
	this->numberOfLayers = neuralNetwork.numberOfLayers;
	this->numberOfInput = neuralNetwork.numberOfInput;
	this->numberOfOutputs = neuralNetwork.numberOfOutputs;
	this->structureOfNetwork = neuralNetwork.structureOfNetwork;
	this->activationFunctionByLayer = neuralNetwork.activationFunctionByLayer;
	this->layers = neuralNetwork.layers;
	this->errors = neuralNetwork.errors;
	this->outputs = neuralNetwork.outputs;
}

bool NeuralNetwork::operator==(const NeuralNetwork& neuralNetwork)
{
	return (this->maxOutputIndex == neuralNetwork.maxOutputIndex
		&& this->lastError == neuralNetwork.lastError
		&& this->learningRate == neuralNetwork.learningRate
		&& this->clusteringRate == neuralNetwork.clusteringRate
		&& this->previousClusteringRate == neuralNetwork.previousClusteringRate
		&& this->error == neuralNetwork.error
		&& this->momentum == neuralNetwork.momentum
		&& this->numberOfResultsClassifiedWell == neuralNetwork.numberOfResultsClassifiedWell
		&& this->numberOfResultsMisclassefied == neuralNetwork.numberOfResultsMisclassefied
		&& this->numberOfHiddenLayers == neuralNetwork.numberOfHiddenLayers
		&& this->numberOfLayers == neuralNetwork.numberOfLayers
		&& this->numberOfInput == neuralNetwork.numberOfInput
		&& this->numberOfOutputs == neuralNetwork.numberOfOutputs
		&& this->structureOfNetwork == neuralNetwork.structureOfNetwork
		&& this->activationFunctionByLayer == neuralNetwork.activationFunctionByLayer
		&& this->layers == neuralNetwork.layers
		&& this->errors == neuralNetwork.errors
		&& this->outputs == neuralNetwork.outputs);
}

bool NeuralNetwork::operator!=(const NeuralNetwork& neuralNetwork)
{
	return !this->operator==(neuralNetwork);
}
