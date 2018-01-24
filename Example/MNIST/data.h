#ifndef DATA_H
#define DATA_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

namespace Data
{
    struct Set
    {
        int size;
        vector<vector<unsigned char>> images;
        vector<unsigned char> labels;
    };

    struct MNIST_struct
    {
       Set testing;
       Set trainig;
    };

    MNIST_struct create_MNIST();
    MNIST_struct Initialize_MNIST();
    void readImages(MNIST_struct &MNIST);
    void readSet(Set &set, ifstream &images, ifstream &labels);
}

#endif // DATA_H
