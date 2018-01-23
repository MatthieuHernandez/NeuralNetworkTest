#include <string>
#include <vector>

using namespace std;

namespace Data
{

const string path_MNIST[4] = {".\\mnist\\t10k-images.idx3-ubyte"
                              ".\\mnist\\t10k-labels.idx1-ubyte"
                              ".\\mnist\\train-images.idx3-ubyte"
                              ".\\mnist\\train-labels.idx1-ubyte"};

struct Set
{
    const int size;
    vector<vector<char>> images;
};

struct MNIST_struct
{
   Set testing;
   Set learning;
};


MNIST_struct* create_MNIST()
{
   MNIST_struct *MNIST = Initialize_MNIST();
   readImages(&MNIST);
}

MNIST_struct* create_MNIST()
{
    MNIST_struct *MNIST = new MNIST_struct();

    MNIST->learning = new Set();
    MNIST->testing = new Set();

    MNIST->learning.size = 60000;
    MNIST->testing.size = 10000;
}

void readImages(MNIST_struct *MNIST)
{
    ifstream imagesTestFile;
    ifstream labelsTestFile;
    ifstream imagesLearnFile;
    ifstream labelsLearnFile;
    imagesTestFile.open(path_MNIST[0], ios::in | ios::binary);
    labelsTestFile.open(path_MNIST[1], ios::in | ios::binary);
    imagesLearnFile.open(path_MNIST[2], ios::in | ios::binary);
    labelsLearnFile.open(path_MNIST[3], ios::in | ios::binary);

    readSet(&MNIST->testing, imagesTestFile, labelsTestFile);
    readSet(&MNIST->learning, imagesLearnFile, labelsLearnFile);
}

void readSet(Set *set, ifstream &images, ifstream &labels)
{
    if(images.is_open() != true
    && labels.is_open() != true)
    {
        cout << "STEP FAILED" << endl;
        return;
    }
    int i = 0;
    int c = 0;

    while(!labels.eof())
    {
        c = labels.get();
        if(c >= 0 && c <= 9 && i > 5)
            set->labels.push_back(c);
        i++;
    }

    i = 0;

    while(!images.eof())
    {
        c = images.get();
        if(c >= 0 && c <= 255 && i > 15)
            set->images.push_back(c);
        i++;
    }
    images.close();
    labels.close();
}

}
