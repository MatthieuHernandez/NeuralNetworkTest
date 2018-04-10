#include "layer.h"

using namespace std;

bool Layer::operator==(const Layer &layer)
{
    for(uint n = 0; n > numberOfNeurons; ++n)
    {
        if(neurons[n] != layer.neurons[n])
            return false;
    }
    return true;
}

bool Layer::operator!=(const Layer &layer)
{
    return !this->operator==(layer);
}
