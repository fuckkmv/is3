//Playfair Cipher Encryption and Decryption Functions
#include <iostream>
#include <string>
using namespace std;

/*Matrix for PlayFair Cipher*/
char matrix[5][5];
string withI = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
string withJ = "ABCDEFGHJKLMNOPQRSTUVWXYZ";

/*Common string utility functions*/
//Function to check if string has a particular alphabet or not
bool hasAlphabet(string word,char alphabet){
	for (int i=0; i<word.length(); i++) {
		if(word[i]==alphabet){
			return true;
		}
	}
	return false;
}

//Function to remove duplicate alphabets from string, keeping only one in string
string removeDuplicateLetter(string str){
	string result;
   	for (int i=0; i<str.length(); i++) {
     	int j;  
     	for (j=0; j<i; j++){
			if (str[i] == str[j]){
        		break;
			}
		}
        if (j == i){
     		result.push_back(str[i]);
		}
   	}
   return result;
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

//Function to replace a alphabet from given alphabet to another given alphabet in string
string changeChar(string str, char from, char to){
	if(hasAlphabet(str, from)){
		for(int i=0; i<str.length(); i++){
			if(str[i]==from){
				str[i]=to;
			}
		}		
	}
	return str;
}

/*Matrix related function*/
//Function to get column index number of given alphabet in matrix
int getColIndex(char ele){
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(matrix[i][j]==ele){
				return j;
			}
		}
	}	
	return -1;
}

//Function to get row index number of given alphabet in matrix
int getRowIndex(char ele){
	for(int i=0; i<5; i++){
		for(int j=0; j<5; j++){
			if(matrix[i][j]==ele){
				return i;
			}
		}
	}
	return -1;
}

//Function to print a 2D matrix
void printMatrix(){
	cout<<endl<<"Matrix:"<<endl;
	for(int i=0;i<5;i++){
		cout<<"|";
		for(int j=0;j<5;j++){
			cout<<" "<<matrix[i][j]<<"|";
		}
		cout<<endl;
	}
}

//Function to fill a matrix with given keyword
void fillMatrix(string keyword){
	keyword= changeToUpper(keyword);
	if(hasAlphabet(keyword,'I')){
		if(hasAlphabet(keyword,'J')){
			keyword= changeChar(keyword, 'J','I');
		}
		keyword+=withI;
	}
	else{
		keyword+=withJ;
	}
    keyword = removeDuplicateLetter(keyword);
	int index = 0;
	for(int i=0;i<5;i++){
		for(int j=0;j<5;j++){
			matrix[i][j]=keyword[index++];
		}
	}
	printMatrix();
}



/*Cipher related functions*/
//Function for using matching row rule of Playfair cipher 
char byRowRule(int row, int col, char ele, bool right){
	if(right==true){
		if(col+1<5){
			return matrix[row][col+1];
		}
		else{
			return matrix[row][0];
		}
	}
	else{
		if(col-1>=0){
			return matrix[row][col-1];
		}
		else{
			return matrix[row][4];
		}
	}
	
}

//Function for using matching column rule of Playfair cipher
char byColRule(int row, int col, char ele, bool below){
	if(below==true){
		if(row+1<5){
			return matrix[row+1][col];
		}
		else{
			return matrix[0][col];
		}
	}
	else{
		if(row-1>=0){
			return matrix[row-1][col];
		}
		else{
			return matrix[4][col];
		}
	}
	
}

//Function to add filler letter between matching pair of alphabet in string, default filler is X
string addFillerLetter(string msg, char letter='X'){
	for (int i = 1; i < msg.length(); i+=2) 
    {
        /*if(msg.at(i-1)==' '){
    		msg = msg + " ";
    		i--;
		}
        else */if (msg.at(i) == msg.at(i - 1)) 
        {
            msg = msg.substr(0, i) + letter + msg.substr(i, msg.length());
        }
    }
	if(msg.length()%2!=0){
		msg.push_back('X');
	}
	return msg;
}

//Function to remove filler letter between two words or matching pair of alphabet in string, default filler is X
string removeFillerLetter(string msg, char letter='X'){
	for (int i = 1; i < msg.length()-1; i++) 
    {
    	if(msg.at(i)=='X'){
    		if(msg.at(i-1)!=msg.at(i+1)){
    			msg = msg.substr(0, i) + " " +msg.substr(i+1, msg.length());
			}
			else{
				msg = msg.substr(0, i) + msg.substr(i+1, msg.length());
			}
		}	
    }
    if(msg[msg.length()-1]=='X'){
    	msg = msg.substr(0, msg.length()-1);
	}
	return msg;
}

//Function to encrypt given string using Playfair cipher
string encryptMsg(string msg){
	msg= addFillerLetter(msg, 'X');
    string encodedMsg;
    for(int i=0; i<msg.length();i++){
        if(isalpha(msg[i])){
        	int r1 = getRowIndex(msg[i]);
        	int r2 = getRowIndex(msg[i+1]);
        	int c1 = getColIndex(msg[i]);
			int c2 = getColIndex(msg[i+1]);
			if(r1==r2){
        		encodedMsg.push_back(byRowRule(r1,c1,msg[i],true));
        		encodedMsg.push_back(byRowRule(r2,c2,msg[i+1],true));
				i++;
			}
			else if(c1==c2){
				encodedMsg.push_back(byColRule(r1,c1,msg[i],true));
        		encodedMsg.push_back(byColRule(r2,c2,msg[i+1],true));
				i++;
			}
			else{
				if(msg[i+1]==' '){
					//Treating Space as X
					r2= getRowIndex('X');
					c2= getColIndex('X');
					encodedMsg.push_back(matrix[r1][c2]);
					encodedMsg.push_back(matrix[r2][c1]);
				}
				else{
					encodedMsg.push_back(matrix[r1][c2]);
					encodedMsg.push_back(matrix[r2][c1]);
				}
				i++;
			}
		}
        else
            encodedMsg.push_back(msg[i]);
    }
    return encodedMsg;
}

//Function to decrypt given string using Playfair cipher
string decryptMsg(string msg){
    string decodedMsg;
    for(int i=0; i<msg.length();i++){
        if(isalpha(msg[i])){
        	int r1 = getRowIndex(msg[i]);
        	int r2 = getRowIndex(msg[i+1]);
        	int c1 = getColIndex(msg[i]);
			int c2 = getColIndex(msg[i+1]);
			if(r1==r2){
        		decodedMsg.push_back(byRowRule(r1,c1,msg[i],false));
        		decodedMsg.push_back(byRowRule(r2,c2,msg[i+1],false));
			}
			else if(c1==c2){
				decodedMsg.push_back(byColRule(r1,c1,msg[i],false));
        		decodedMsg.push_back(byColRule(r2,c2,msg[i+1],false));
			}
			else{
				decodedMsg.push_back(matrix[r1][c2]);
				decodedMsg.push_back(matrix[r2][c1]);
			}
			i++;
		}
        else
            decodedMsg.push_back(msg[i]);
    }
    return decodedMsg;
}

//Function to get keyword from user
string getKeyword(){
    string keyword;
    cout<<endl<<"Enter your keyword:";
    getline(cin>>ws,keyword);
    return keyword;
}

/*Menu related function*/
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
    string keyword;
    string noFiller;
    string decodedMsg;
    string encodedMsg;
    char choice;

    do{
        choice = getChoice();
        
        switch(choice){
            case '1':
                cout<<endl<<"Enter PlainText to Encrypt:";
                getline(cin>>ws, msg);
                msg = changeToUpper(msg);
                keyword = getKeyword();
                fillMatrix(keyword);
                msg = addFillerLetter(msg);
                encodedMsg = encryptMsg(msg);
                cout<<endl<<"--> Encoded Message CiperText: "<<encodedMsg<<endl;
                break;
            case '2':
                cout<<endl<<"Enter CiperText to Decrypt:";
                getline(cin>>ws, msg);
                msg = changeToUpper(msg);
                keyword = getKeyword();
				fillMatrix(keyword);
                decodedMsg = decryptMsg(msg);
                //cout<<endl<<"--> Decoded Message PlainText: "<<decodedMsg<<endl;
                noFiller= removeFillerLetter(decodedMsg);
                cout<<endl<<"--> Decoded Message PlainText: "<<noFiller<<endl;
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
	cout<<"************Playfair Cipher Method************"<<endl;
    menu();
    return 0;
}
