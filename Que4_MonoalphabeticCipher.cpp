//Monoalphabetic Cipher Encryption and Decryption Functions
#include <iostream>
#include <string>
using namespace std;

//Function to encrypt given string using Monoalphabetic Cipher
string encryptMsg(string msg, int key){
    string encodedMsg;
    for(int i=0; i<msg.length();i++){
        if(msg[i]>='A' && msg[i]<='Z'){
            int c = int(msg[i]);
            int d = c-65;
            int e = (d+key)%26;
            encodedMsg.push_back(char(e+65));
        }
        else if(msg[i]>='a' && msg[i]<='z'){
            int c = int(msg[i]);
            int d = c-97;
            int e = (d+key)%26;
            encodedMsg.push_back(char(e+97));
        }
        else
            encodedMsg.push_back(msg[i]);
    }
    return encodedMsg;
}

//Function to decrypt given string using Monoalphabetic Cipher
string decryptMsg(string msg, int key){
    string decodedMsg;
    for(int i=0; i<msg.length();i++){
        if(msg[i]>='A' && msg[i]<='Z'){
            int c = int(msg[i]);
            int d = c-65;
            int e;
            if(d<key){
                e = 26+(d-key);
            }
            else{
                e = (d-key)%26;
            }
            decodedMsg.push_back(char(e+65));
        }
        else if(msg[i]>='a' && msg[i]<='z'){
            int c = int(msg[i]);
            int d = c-97;
            int e;
            if(d<key){
                e = 26+(d-key);
            }
            else{
                e = (d-key)%26;
            }
            decodedMsg.push_back(char(e+97));
        }
        else
            decodedMsg.push_back(msg[i]);
    }
    return decodedMsg;
}

//Function to get key from user
int getKey(){
    int key;
    cout<<endl<<"Enter your key:";
    cin>>key;
    if(key>=1&&key<=26){
		return key;
	}
    else{
    	cout<<"Please enter the key within range(1-26)......";
    	return getKey();
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
    int key;
    string decodedMsg;
    string encodedMsg;
    char choice;

    do{
        choice = getChoice();
        
        switch(choice){
            case '1':
                cout<<endl<<"Enter PlainText to Encrypt:";
                getline(cin>>ws, msg);
                key = getKey();
                encodedMsg = encryptMsg(msg,key);
                cout<<endl<<"--> Encoded Message CiperText: "<<encodedMsg<<endl;
                break;
            case '2':
                cout<<endl<<"Enter CiperText to Decrypt:";
                getline(cin>>ws, msg);
                key = getKey();
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
	cout<<"************Monoalphabetic Cipher Method************"<<endl;
    menu();
    return 0;
}
