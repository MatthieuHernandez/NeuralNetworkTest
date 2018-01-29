#include "NeuralNetwork.h"

bool NeuralNetwork::isTheFirst = true;

NeuralNetwork::NeuralNetwork()
{

}

NeuralNetwork::NeuralNetwork(int numberOfInputs, int numberOfHiddenLayers, int numberOfNeuronsInHiddenLayers, int numberOfOutputs, float learningRate)
{
    // IS VIRGIN
    if(isTheFirst == true)
    {
        srand(time(NULL));
        rand();
        isTheFirst = false;
    }
    this->learningRate = learningRate;
    this->lenghtOfShortRuns = 0;
    this->shortRunCounter = 0;
    this->numberOfResultsClassifiedWell = 0;
    this->numberOfResultsMisclassefied = 0;
    this->clusteringRate = -1;
    this->numberOfInput = numberOfInputs;
    this->numberOfHiddenLayers = numberOfHiddenLayers;
    this->numberOfLayers = this->numberOfHiddenLayers+1;
    this->numberOfNeuronsInHiddenLayers = numberOfNeuronsInHiddenLayers;
    this->numberOfOutput = numberOfOutputs;
    this->momentum = 0;
    this->lastError = 0;
    this->error = 0;
    this->numberOfResultsClassifiedWell = 0;

    outputs.resize(numberOfOutput);

    vector<Perceptron> temp;
    vector<float> temp2;
    neurons.push_back(temp);
    results.push_back(temp2);
    errors.push_back(temp2);
    for (unsigned int i = 0; i < this->numberOfNeuronsInHiddenLayers; i++) // layer 0
    {
        neurons[0].push_back(Perceptron(this->numberOfInput, 0, i)); // this->numberOfInputs
        results[0].push_back(0);
        errors[0].push_back(0);
    }
    for (unsigned int i = 1; i < this->numberOfHiddenLayers; i++) // layers
    {
        neurons.push_back(temp);
        results.push_back(temp2);
        errors.push_back(temp2);
        for(unsigned int j = 0;  j < this->numberOfNeuronsInHiddenLayers; j++) // output neuron
        {
            neurons[i].push_back(Perceptron(numberOfNeuronsInHiddenLayers, i, j));

            results[i].push_back(0);
            errors[i].push_back(0);
        }
    }
    neurons.push_back(temp);
    results.push_back(temp2);
    errors.push_back(temp2);
    for(unsigned int i = 0; i < this->numberOfOutput; i++)
    {
        neurons[numberOfHiddenLayers].push_back(Perceptron(this->numberOfNeuronsInHiddenLayers, numberOfHiddenLayers, i, false));
        results[numberOfHiddenLayers].push_back(0);
        errors[numberOfHiddenLayers].push_back(0);
    }
}

vector<float> NeuralNetwork::calculateOutput(const vector<float> &inputs)
{
    for(unsigned int n = 0; n < neurons[0].size(); n++) // first layer
    {
       results[0][n] = neurons[0][n].outputFloat(inputs);
    }
    for(unsigned int l = 1; l < numberOfHiddenLayers; l++) // hidden layers
    {
        for(unsigned int n = 0; n < neurons[l].size(); n++)
        {
           results[l][n] = neurons[l][n].outputFloat(results[l-1]);
        }
    }
    for(int n = 0; n < neurons[numberOfHiddenLayers].size(); n++)
    {
       results[numberOfHiddenLayers][n] = neurons[numberOfHiddenLayers][n].outputFloat(results[numberOfHiddenLayers-1])/2.0f + 0.5f; // between 0 and 1
    }
    return results[numberOfHiddenLayers];
}

void NeuralNetwork::calculateClusteringRateForRegressionProblem(const vector<float> &inputs, const vector<int> &desired)
{
    this->calculateOutput(inputs);
    for(int i = 0; i < results[numberOfHiddenLayers].size(); i++)
    {
        classifiedWell = true;
        if((int)round(results[numberOfHiddenLayers][i]) == desired[i] && desired[i] != -1.0)
        {
            classifiedWell = false;
            break;
        }
    }
    if(classifiedWell == true)
    {
        numberOfResultsClassifiedWell++;
    }
    else
    {
        numberOfResultsMisclassefied++;
    }

}

void NeuralNetwork::calculateClusteringRateForClassificationProblem(const vector<float> &inputs, const int classNumber)
{
    maxOutputValue = 0;
    this->calculateOutput(inputs);

    for(int i = 0; i < results[numberOfHiddenLayers].size(); i++)
    {
        if(maxOutputValue < results[numberOfHiddenLayers][i])
        {
            maxOutputValue = results[numberOfHiddenLayers][i];
            maxOutputIndex = i;
        }
    }
    if(maxOutputIndex == classNumber)
    {
        numberOfResultsClassifiedWell++;
    }
    else
    {
        numberOfResultsMisclassefied++;
    }
}

void NeuralNetwork::train(const vector<float> &inputs, const vector<float> &desired)
{
    backpropagationAlgorithm(inputs, desired);
}

void NeuralNetwork::backpropagationAlgorithm(const vector<float> &inputs, const vector<float> &desired)
{
    this->calculateOutput(inputs);

    for(unsigned int i = 0; i < numberOfOutput; i++) // for each neurons in upper layer
    {
        if(desired[i] != -1.0f)
        {
            errors[numberOfHiddenLayers][i] = desired[i] - results[numberOfHiddenLayers][i];
            //errors[numberOfHiddenLayers][i] = (float)errors[numberOfHiddenLayers][i] * (float)abs(errors[numberOfHiddenLayers][i]);
        }
        else
            errors[numberOfHiddenLayers][i] = 0;
    }
    for(int l = (int)(neurons.size()-1); l >= 0; l--) // from last hidden layer to first layer
    {
        for(unsigned int n = 0; n < neurons[l].size(); n++)
        {
            if(l < (int)numberOfHiddenLayers)
            {
                calculateError(l, n);
            }
        }
    }
    for(int l = (int)(neurons.size()-1); l >= 0; l--) // from last hidden layer to first layer
    {
        for(unsigned int n = 0; n < neurons[l].size(); n++)
        {
            if(l == 0)
                neurons[l][n].trainWithError(inputs, errors[l][n], learningRate, momentum);
            else
                neurons[l][n].trainWithError(results[l-1], errors[l][n], learningRate, momentum);
        }
    }
}

void NeuralNetwork::calculateError(const int neuronNumberLayer, const int neuronNumber) // TO RE READ
{
    float error = 0;
    for(int i = 0; i < neurons[neuronNumberLayer+1].size(); i++) // for each neurons in upper layer
    {
        error += errors[neuronNumberLayer+1][i] * neurons[neuronNumberLayer+1][i].getWeight(neuronNumber);
    }
    errors[neuronNumberLayer][neuronNumber] = error;
}

void NeuralNetwork::resetAllNeurons()
{
    for(int i = 0; i < neurons.size(); i++)
    {
        for(int j = 0; j < neurons[i].size(); j++)
        {
            neurons[i][j] = Perceptron(neurons[i][j].getNumberOfInputs(), neurons[i][j].getLayerNumber(), neurons[i][j].getNumberInLayer(), false);
        }
    }
}

void NeuralNetwork::addANeuron(unsigned int layerNumber, bool isVirgin)
{
    results[layerNumber].push_back(0);
    errors[layerNumber].push_back(0);
    outputs.push_back(0);

    if(layerNumber == 0)
    {
        numberOfInput ++;
        neurons[layerNumber].push_back(Perceptron(neurons[layerNumber][0].getWeights().size(), layerNumber, numberOfInput-1, isVirgin));
        for(unsigned int i = 0; i < neurons[layerNumber+1].size(); i++)
        {
            neurons[layerNumber+1][i].addAWeight(isVirgin);
        }

    }
    else if(layerNumber == numberOfHiddenLayers)
    {
        numberOfOutput ++;
        neurons[layerNumber].push_back(Perceptron(neurons[layerNumber][0].getWeights().size(), layerNumber, numberOfOutput-1, isVirgin));

    }
    else if(layerNumber > 0 && layerNumber < numberOfHiddenLayers)
    {
        numberOfNeuronsInHiddenLayers ++;
        for(int j = 1;  j < numberOfHiddenLayers; j++) // output neuron
        {
            neurons[j].push_back(Perceptron(neurons[j][0].getWeights().size(), j, numberOfNeuronsInHiddenLayers-1, isVirgin));
            for(int i = 0; i < neurons[j+1].size(); i++)
            {
                neurons[j+1][i].addAWeight(isVirgin);
            }
        }
    }
    else
    {
        cout << "ERROR IN ADD NEURON" << endl;
        lastError = 8;
    }
    cout << "neuron added" << endl;
}

int NeuralNetwork::isValid()
{
    unsigned int real_sum = 0;
    unsigned int virtual_sum = 0;

    for(unsigned int i = 0; i < neurons.size(); i++)
    {
        if(((unsigned int)neurons[i].size() != numberOfNeuronsInHiddenLayers && i < numberOfHiddenLayers)
        || ((unsigned int)neurons[i].size() != numberOfOutput && i == numberOfHiddenLayers))
        {
            cout << "i = " << i << endl;
            cout << numberOfNeuronsInHiddenLayers << endl;
            cout << neurons[i].size() << endl;
            lastError = 10;
            return lastError;
        }
    }
    for(unsigned int i = 0; i < neurons.size(); i++)
    {
        for(unsigned int j = 0; j < neurons[i].size(); j++)
        {
           real_sum += neurons[i][j].getNumberOfInputs();
        }
    }

    virtual_sum += numberOfNeuronsInHiddenLayers*numberOfInput + numberOfNeuronsInHiddenLayers*numberOfOutput + (int)pow(numberOfNeuronsInHiddenLayers, 2) * (numberOfHiddenLayers-1);

    if(real_sum != virtual_sum)
    {
        lastError = 11;
        cout << real_sum << endl;
        cout << virtual_sum << endl;
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
    for(unsigned int i = 0; i < neurons.size(); i++)
    {
        for(unsigned int j = 0; j < neurons[i].size(); j++)
        {
            if(neurons[i][j].isValid() != 0)
            {
              lastError = neurons[i][j].isValid();
              return lastError;
            }
        }
    }
    return 0;
}

int NeuralNetwork::getLastError()
{
    return lastError;
}

bool NeuralNetwork::operator==(const NeuralNetwork &neuralNetwork)
{
    if(this->numberOfInput != neuralNetwork.numberOfInput
    || this->numberOfHiddenLayers != neuralNetwork.numberOfHiddenLayers
    || this->numberOfNeuronsInHiddenLayers != neuralNetwork.numberOfNeuronsInHiddenLayers
    || this->neurons.size() !=  neuralNetwork.neurons.size())
        return false;

    for(int i = 0; i < this->neurons.size(); i++)
    {
        if(this->neurons.size() !=  neuralNetwork.neurons.size())
            return false;
        for(int j = 0; j < this->neurons[i].size(); j++)
            if(this->neurons[i][j] != neuralNetwork.neurons[i][j])
                return false;
    }
    return true;
}

bool NeuralNetwork::operator!=(const NeuralNetwork &neuralNetwork)
{
    if(this->operator==(neuralNetwork))
        return false;
    else
        return true;
}

string NeuralNetwork::display()
{
   string str;
   str = "Learning rate : " + to_string(learningRate);
    for(int i = 0; i < neurons.size(); i++)
    {
        str += "Layer " + to_string(i) + " :\n";
        for(int j = 0; j < neurons[i].size(); j++)
        {
            str += neurons[i][j].display();
            str += "\n";
        }
    }
    return str;
}
