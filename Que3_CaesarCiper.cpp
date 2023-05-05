//Caesar Cipher Encryption and Decryption Functions
#include <iostream>
#include <string>

using namespace std;

//Function to encrypt given string using Caesar Cipher
string encryptMsg(string msg){
    string encodedMsg;
    for(int i=0; i<msg.length();i++){
        if(msg[i]>='A' && msg[i]<='Z'){
            int c = int(msg[i]);
            int d = c-65;
            if(d>=0 && d<23){
                c+=3;
                encodedMsg.push_back(char(c));
            }
            else{
                encodedMsg.push_back(char(c-23));
            }
        }
        else if(msg[i]>='a' && msg[i]<='z'){
            int c = int(msg[i]);
            int d = c-97;
            if(d>=0 && d<23){
                c+=3;
                encodedMsg.push_back(char(c));
            }
            else{
                encodedMsg.push_back(char(c-23));
            }
        }
        else
            encodedMsg.push_back(msg[i]);
    }
    return encodedMsg;
}

//Function to decrypt given string using Caesar Cipher
string decryptMsg(string msg){
    string decodedMsg;
    for(int i=0; i<msg.length();i++){
        if(msg[i]>='A' && msg[i]<='Z'){
            int c = int(msg[i]);
            int d = c-65;
            if(d>=3 && d<=25){
                c-=3;
                decodedMsg.push_back(char(c));
            }
            else{
                decodedMsg.push_back(char(c+23));
            }
        }
        else if(msg[i]>='a' && msg[i]<='z'){
            int c = int(msg[i]);
            int d = c-97;
            if(d>=3 && d<=25){
                c-=3;
                decodedMsg.push_back(char(c));
            }
            else{
                decodedMsg.push_back(char(c+23));
            }
        }
        else
            decodedMsg.push_back(msg[i]);
    }
    return decodedMsg;
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
	
    char choice;
	do{
		string msg;
		string decodedMsg;
	    string encodedMsg;
	    choice = getChoice();
	    
	    switch(choice){
	    	case '1':
	    		cout<<endl<<"Enter PlainText to Encrypt: ";
			    getline (cin >> ws, msg);
			    encodedMsg = encryptMsg(msg);
			    cout<<endl<<"--> Encoded Message CiperText: "<<encodedMsg<<endl;
	    		break;
	    	case '2':
	    		cout<<endl<<"Enter CiperText to Decrypt: ";
			    getline (cin >> ws, msg);
			    decodedMsg = decryptMsg(msg);
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
    cout<<"**************Caesar Cipher Method**************"<<endl;
    menu();
    return 0;
}
