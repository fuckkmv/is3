//Rail Fence Transposition Cipher Encryption and Decryption Functions
#include <iostream>
#include <string>
using namespace std;

//Function to change characters of string to choosen generalised case
string generaliseCase(string str, bool upper=true){
	string result;
	for(int i=0; i<str.length(); i++){
		if(isalpha(str[i]))
			if(upper)
				result.push_back(toupper(str[i]));
			else
				result.push_back(tolower(str[i]));
		else
			result.push_back(str[i]);
	}
	return result;
}

//Function to encrypt given string using Rail Fence Cipher
string encryptMsg(string msg, int key){
	string encodedMsg;
	int columnSize= msg.length();
	char matrix[key][columnSize];
	
	for(int i=0; i<key;i++){
    	for(int j=0; j<columnSize; j++){
    		matrix[i][j]='-';
		}
    }
    
	bool down=true;
    int currentRow=0, j=0;
    for(int i=0; i<columnSize;i++){
    	if(down){
    		matrix[currentRow][i]=msg[j];
    		j++;
    		currentRow++;
			if(currentRow==(key)){
				down=false;
				currentRow--;
				i++;
			}	
		}
		
		if(!down){
			currentRow--;
			matrix[currentRow][i]=msg[j];
			j++;
			if(currentRow==0){
				down=true;
				currentRow++;
			}
		}
		
    }
    
    for(int i=0; i<key;i++){
    	for(int j=0; j<columnSize; j++){
    		if(isalpha(matrix[i][j])){
    			encodedMsg.push_back(matrix[i][j]);
			}
			cout<<matrix[i][j]<<"|";
		}
		cout<<endl;
    }
    return encodedMsg;
}

//Function to decrypt given string using Rail Fence Cipher
string decryptMsg(string msg, int key){
    string decodedMsg;
	int columnSize= msg.length();
	char matrix[key][columnSize];
	
	for(int i=0; i<key;i++){
    	for(int j=0; j<columnSize; j++){
    		matrix[i][j]='-';
		}
    }
    
	bool down=true;
    int currentRow=0, j=0;
    for(int i=0; i<columnSize;i++){
    	if(down){
    		matrix[currentRow][i]=msg[j];
    		j++;
    		currentRow++;
			if(currentRow==(key)){
				down=false;
				currentRow--;
				i++;
			}	
		}
		
		if(!down){
			currentRow--;
			matrix[currentRow][i]=msg[j];
			j++;
			if(currentRow==0){
				down=true;
				currentRow++;
			}
		}	
    }
    int k=0;
    for(int i=0; i<key;i++){
    	for(int j=0; j<columnSize; j++){
    		if(isalpha(matrix[i][j])){
    			matrix[i][j]=msg[k];
    			k++;
			}
			cout<<matrix[i][j]<<"|";
		}
		cout<<endl;
    }
    currentRow=0;
    for(int i=0; i<columnSize;i++){
    	if(down){
    		decodedMsg.push_back(matrix[currentRow][i]);
    		currentRow++;
			if(currentRow==(key)){
				down=false;
				currentRow--;
				i++;
			}	
		}	
		if(!down){
			currentRow--;
			decodedMsg.push_back(matrix[currentRow][i]);
			if(currentRow==0){
				down=true;
				currentRow++;
			}
		}	
    }
    
    return decodedMsg;
}

//Function to get key from user
int getKey(){
    int key;
    cout<<endl<<"Enter your key number:";
    cin>>key;
    return key;
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
                msg= generaliseCase(msg, false);
                key = getKey();
                encodedMsg = encryptMsg(msg,key);
                cout<<endl<<"--> Encoded Message CiperText: "<<encodedMsg<<endl;
                break;
            case '2':
                cout<<endl<<"Enter CiperText to Decrypt:";
                getline(cin>>ws, msg);
                msg= generaliseCase(msg, false);
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
	cout<<"************Rail Fence Transposition Cipher Method************"<<endl;
    menu();
    return 0;
}
