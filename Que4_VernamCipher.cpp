//Vernam Cipher Encryption and Decryption Functions
#include <iostream>
#include <string>
using namespace std;

//Function to encrypt given string using Vernam Cipher
string encryptMsg(string msg, string key){
    string encodedMsg;
    for(int i=0; i<key.length();i++){
        int pi = int(msg[i]);
        int ki = int(key[i]);
		int ci = (pi xor ki);
        encodedMsg.push_back(char(ci));
    }
    return encodedMsg;
}

//Function to decrypt given string using Vernam Cipher
string decryptMsg(string msg, string key){
    string decodedMsg;
    for(int i=0; i<key.length();i++){
        int ci = int(msg[i]);
        int ki = int(key[i]);
		int pi = (ci xor ki);
        decodedMsg.push_back(char(pi));
    }
    return decodedMsg;
}

//Function to get key from user
string getKey(string msg, bool modified_version=false){
    string key;
    cout<<endl<<"Enter your key:";
    getline(cin>>ws, key);
    if(key.length()>msg.length()){
    	cout<<"Please enter the key with length less than text......";
    	return getKey(msg);
	}
	else{
		string newKey = key;
		if(modified_version){
			newKey += msg.substr(0, msg.length()-key.length());
		}
		else{
			for(int i=key.length(), j=0; i<msg.length();i++,j++){
				if(j==key.length()){
					j=0;
				}
				newKey.push_back(key[j]);
			}
		}
		return newKey;
	}
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
                cout<<endl<<"Enter PlainText to Encrypt:";
                getline(cin>>ws, msg);
                key = getKey(msg);
                encodedMsg = encryptMsg(msg,key);
                cout<<endl<<"--> Encoded Message CiperText: "<<encodedMsg<<endl;
                decodedMsg = decryptMsg(encodedMsg,key);
                cout<<endl<<"--> Decoded Message PlainText: "<<decodedMsg<<endl;
                break;
            case '2':
                cout<<endl<<"Enter CiperText to Decrypt:";
                getline(cin>>ws, msg);
                key = getKey(msg);
                decodedMsg = decryptMsg(msg,key);
                cout<<endl<<"--> Decoded Message PlainText: "<<decodedMsg<<endl;
                break;
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

//Main function for execution of program
int main() {
	cout<<"************Vernam Cipher Method************"<<endl;
    menu();
    return 0;
}
