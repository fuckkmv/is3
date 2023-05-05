//Error Correcting Code

#include <iostream>
#include <vector>

using namespace std;

// Calculates the number of parity bits needed for a given data length
int calculateParityBits(int n)
{
    int m = 0;
    while ((1 << m) < n + m + 1)
    {
        m++;
    }
    return m;
}

// Adds parity bits to the data vector
void addParityBits(vector<int> &data)
{
    int m = calculateParityBits(data.size());

    for (int i = 0; i < m; i++)
    {
        int parityBit = 0;
        for (int j = 1; j <= data.size(); j++)
        {
            if (j & (1 << i))
            {
                parityBit ^= data[j - 1];
            }
        }
        data.insert(data.begin() + (1 << i) - 1, parityBit);
    }
}

// Calculates the syndrome for a given code word and returns the index of the error bit
int calculateSyndrome(vector<int> &codeWord)
{
    int m = calculateParityBits(codeWord.size());

    int syndrome = 0;
    for (int i = 0; i < m; i++)
    {
        int parityBit = 0;
        for (int j = 1; j <= codeWord.size(); j++)
        {
            if (j & (1 << i))
            {
                parityBit ^= codeWord[j - 1];
            }
        }
        syndrome |= parityBit << i;
    }
    return syndrome;
}

// Corrects the error in the code word by flipping the error bit
void correctError(vector<int> &codeWord, int errorBit)
{
    codeWord[errorBit - 1] ^= 1;
}

// Main function
int main()
{
    vector<int> data = {1, 0, 1, 1};
    cout<<"Data : ";
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
    addParityBits(data);

    cout << "Data with parity bits:";
    for (int i = 0; i < data.size(); i++)
    {
        cout << " " << data[i];
    }
    cout << endl;

    // Introduce an error in the code word
    data[2] ^= 1;

    cout << "Code word with error:";
    for (int i = 0; i < data.size(); i++)
    {
        cout << " " << data[i];
    }
    cout << endl;

    int errorBit = calculateSyndrome(data);
    cout << "Error bit: " << errorBit << endl;

    correctError(data, errorBit);

    cout << "Corrected code word:";
    for (int i = 0; i < data.size(); i++)
    {
        cout << " " << data[i];
    }
    cout << endl;

    return 0;
}
