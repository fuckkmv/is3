//Error Detecting Code
#include <iostream>
#include <vector>

using namespace std;

// Calculates the parity bit for a given data vector
int calculateParityBit(vector<int>& data) {
    int parityBit = 0;
    for (int i = 0; i < data.size(); i++) {
        parityBit ^= data[i];
    }
    return parityBit;
}

// Main function
int main() {
    vector<int> data = {1, 0, 1, 1};
    cout<<"Sender : "<<endl;
    cout<<"Data : ";
    for(int i=0;i<data.size();i++){
        cout<<data[i]<<" ";
    }
    cout<<endl;
    int parityBit = calculateParityBit(data);

    // Introduce an error in the data
    data[2] ^= 1;
    cout<<endl<<"Reciver : "<<endl;

    cout << "Data with error:";
    for (int i = 0; i < data.size(); i++) {
        cout << " " << data[i];
    }
    cout << endl;

    int newParityBit = calculateParityBit(data);
    if (newParityBit == parityBit) {
        cout << "No error detected" << endl;
    } else {
        cout << "Error detected" << endl;
    }

    return 0;
}
