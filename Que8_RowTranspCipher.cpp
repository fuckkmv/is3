//Row Transposition Cipher Encryption and Decryption Functions
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//Function to print string as 2D matrix
void displayAsMatrix(string message, string key){
    int keyLen = key.length();
    int messageLen = message.length();
    int index=0;
    cout<<endl;
    for (int i = 0; i < messageLen / keyLen; i++) {
        for (int j = 0; j < keyLen; j++) {
            cout<<message[index]<<"|";
            index++;
        }
        cout<<endl;
    }
}

//Function to change characters of string to upper case
string changeToUpper(string str){
	string result;
	for(int i=0; i<str.length(); i++){
		if(isalpha(str[i]))
			result.push_back(toupper(str[i]));
		else
			result.push_back(str[i]);
	}
	return result;
}

// Function to encrypt the message using Row Transposition Cipher
string encryptMsg(string message, string key) {
    int keyLen = key.length();
    int messageLen = message.length();

    // Pad the message with X's if its length is not a multiple of the key length
    if (messageLen % keyLen != 0) {
        messageLen += keyLen - (messageLen % keyLen);
        message.append(messageLen - message.length(), 'X');
    }

    // Initialize the encryption matrix with the message characters
    char matrix[messageLen / keyLen][keyLen];
    int k = 0;
    for (int i = 0; i < messageLen / keyLen; i++) {
        for (int j = 0; j < keyLen; j++) {
            matrix[i][j] = message[k++];
        }
    }
    cout<<endl<<"Plain Text Matrix:-";
    displayAsMatrix(message, key);
    // Sort the rows of the matrix according to the key
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
    int index[keyLen];
    for (int i = 0; i < keyLen; i++) {
        index[i] = key.find(sortedKey[i]);
    }

    // Concatenate the characters in the sorted rows
    string ciphertext = "";
    for (int i = 0; i < messageLen / keyLen; i++) {
        for (int j = 0; j < keyLen; j++) {
            ciphertext += matrix[i][index[j]];
        }
    }
    cout<<endl<< "Cipher Text :- ";
    return ciphertext;
}

// Function to decrypt the message using Row Transposition Cipher
string decryptMsg(string ciphertext, string key) {
    int keyLen = key.length();
    int ciphertextLen = ciphertext.length();

    // Initialize the decryption matrix with the ciphertext characters
    char matrix[ciphertextLen / keyLen][keyLen];
    int k = 0;
    for (int i = 0; i < ciphertextLen / keyLen; i++) {
        for (int j = 0; j < keyLen; j++) {
            matrix[i][j] = ciphertext[k++];
        }
    }

    // Sort the rows of the matrix according to the key
    string sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
    int index[keyLen];
    for (int i = 0; i < keyLen; i++) {
        index[i] = sortedKey.find(key[i]);
    }
    cout<<endl<<"Cipher Text Matrix:-";
    displayAsMatrix(ciphertext, key);
    // Initialize the decryption message with the matrix characters
    string message = "";
    for (int i = 0; i < ciphertextLen / keyLen; i++) {
        for (int j = 0; j < keyLen; j++) {
            message += matrix[i][index[j]];
        }
    }

    // Remove the padding X's from the decrypted message
    message.erase(remove(message.begin(), message.end(), 'X'), message.end());
    cout<<endl<< "Plain Text :- ";
    return message;
}

//Function to take choice of user from given options
char getChoice(){
    char choice;
    cout<<endl<<"Enter 1 for Encrypt a message....";
    cout<<endl<<"Enter 2 for Decrypt a message....";
    cout<<endl<<"Enter 3 for Exit....";
    cout<<endl<<"Enter >> ";
    cin>>choice;
    return choice; 
}

//Function to perform operations based on user choice
void menu(){
	
    string msg;
    string key;
    string decodedMsg;
    string encodedMsg;
    char choice;

    do{
        choice = getChoice();
        
        switch(choice){
            case '1':
	    	{
		        cout<<endl<<"Enter PlainText to Encrypt:";
	            getline(cin>>ws, msg);
	            cout << "Enter Key as String: ";
		        getline(cin>>ws, key);
		        msg = changeToUpper(msg);
		        cout<<endl<< encryptMsg(msg,key);
		        break;
		    }
		    case '2':
		    {
		        cout<<endl<<"Enter CiperText to Decrypt:";
	            getline(cin>>ws, msg);
		        cout << "Enter Key as String: ";
		        getline(cin>>ws, key);
		        msg = changeToUpper(msg);
		        cout <<decryptMsg(msg,key);
		        break;
		    }
            case '3':
                return;
                break;
            default:
                cout<<endl<<"!!! Entered Choice is not available in this program !!!";
        }
        cout<<endl<<"Want to run the program again? (Y/N):";
        cin>>choice;
        choice = tolower(choice);
    }while(choice!='n');      
}

int main() {
cout<<endl<<"*******************Row Transposition Cipher********************"<<endl;
    menu();
    return 0;
}
