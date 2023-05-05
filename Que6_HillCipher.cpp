//Hill Cipher Encryption and Decryption Functions
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

int keyMat[3][3];


//Function to handle mod of negative and postive number
int getIntMod(int num, int modby){
	if(num>=0){
		return num%modby;
	}
	else{
		int positiveVal = abs(num);
		int bigger=0;	
		for(int i=1; bigger<positiveVal;i++){
			bigger= i*modby;
		}
		return bigger-positiveVal;
	}
}

//Function to get key matrix from user
void getKeyMatrix()
{
	cout<<"Enter elements of 3x3 Key Matrix:"<<endl;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
        	cout<<"-->";
            cin >> keyMat[i][j];
        }
    }
}

//Function to print a 2D matrix
void printMatrix(){
	cout<<endl<<"Matrix:"<<endl;
	for(int i=0;i<3;i++){
		cout<<"|";
		for(int j=0;j<3;j++){
			cout<<" "<<keyMat[i][j]<<"|";
		}
		cout<<endl;
	}
}

//Function to add filler letter between matching pair of alphabet in string, default filler is X
string addFillerLetter(string msg, char letter='X'){
	if (msg.length() % 3 != 0)
        for (int i = msg.length() % 3; i < 3; i++)
            msg += letter;
	return msg;
}

int getDeterminantInverse(int mat[3][3])
{
	int det = 0,detInv = 0;
	det+=mat[0][0]*((mat[1][1]*mat[2][2])-(mat[1][2]*mat[2][1]))-mat[0][1]
					*((mat[1][0]*mat[2][2])-(mat[1][2]*mat[2][0]))+mat[0][2]
					*((mat[1][0]*mat[2][1])-(mat[1][1]*mat[2][0]));
	det%=26;
	if(det<0)
		det+=26;
	for(int i=1;i<=det;i++){
		detInv=(i*det)%26;
		if(detInv==1)
			return i;	
	}
	return -1;
}

void getAdjoin(int mat[3][3],int mat2[3][3])
{
	mat2[0][0]=(mat[1][1]*mat[2][2])-(mat[1][2]*mat[2][1]);
	mat2[1][0]=-((mat[1][0]*mat[2][2])-(mat[1][2]*mat[2][0]));
	mat2[2][0]=(mat[1][0]*mat[2][1])-(mat[1][1]*mat[2][0]);
	mat2[0][1]=-((mat[0][1]*mat[2][2])-(mat[0][2]*mat[2][1]));
	mat2[1][1]=(mat[0][0]*mat[2][2])-(mat[0][2]*mat[2][0]);
	mat2[2][1]=-((mat[0][0]*mat[2][1])-(mat[0][1]*mat[2][0]));
	mat2[0][2]=(mat[0][1]*mat[1][2])-(mat[0][2]*mat[1][1]);
	mat2[1][2]=-((mat[0][0]*mat[1][2])-(mat[0][2]*mat[1][0]));
	mat2[2][2]=(mat[0][0]*mat[1][1])-(mat[0][1]*mat[1][0]);
}

//Function to get Inverse of matrix
void getInv(int det,int mat[3][3],int mat2[3][3])
{
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			mat2[i][j]=det*mat[i][j];
			mat2[i][j]%=26;
			if(mat2[i][j]<0)
				mat2[i][j]+=26;
		}
	}
}

//Function to encrypt the message using Hill Cipher
string encryptMsg(string msg, int key[][3]){
	int CTMatrix[3];
	int PTMatrix[3];
	int msgLen = msg.length();
	string encodedMsg;
	int current = 0;
	while(current!=msgLen){
		int c = current;
		for(int i=0; i<3;i++){
			PTMatrix[i]=int(msg[current+i])-65;
		}
		for(int i=0; i<3;i++){
			CTMatrix[i]=((PTMatrix[0]*key[0][i])+(PTMatrix[1]*key[1][i])+(PTMatrix[2]*key[2][i]));
			encodedMsg.push_back(char(getIntMod(CTMatrix[i],26))+'A');
		}
		current+=3;
	}
	
	return encodedMsg;
}

//Function to decrypt the message using Hill Cipher
string decryptMsg(string msg)
{
    string decodedMsg = "";
    int adj[3][3];
    int inv[3][3];
	int detInv = getDeterminantInverse(keyMat);
	
	getAdjoin(keyMat,adj);
	getInv(detInv,adj,inv);
	
    for (int i = 0; i < msg.length(); i += 3)
    {
        int C[3] = {(msg.at(i)-65) % 26, (msg.at(i+1)-65) % 26, (msg.at(i+2)-65) % 26};

        int PT[3];

        for (int c = 0; c < 3; c++)
        {
			PT[c] = ((C[0] * inv[0][c]) + (C[1] * inv[1][c]) + (C[2] * inv[2][c]))%26;
			if(PT[c]<0)
				PT[c]+=26;
		}
        decodedMsg+=(char)(PT[0]+97);
		decodedMsg+=(char)(PT[1]+97);
		decodedMsg+=(char)(PT[2]+97);
    }
    return decodedMsg;
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
	            cout << "Enter key matrix for encryption" << endl;
		        getKeyMatrix();
		        msg = changeToUpper(msg);
		        msg = addFillerLetter(msg);
		        cout << "Cipher Text :- " << encryptMsg(msg,keyMat);
		        break;
		    }
		    case '2':
		    {
		        cout<<endl<<"Enter CiperText to Decrypt:";
	            getline(cin>>ws, msg);
		        cout << "Enter key matrix for decryption" << endl;
		        getKeyMatrix();
		        msg = changeToUpper(msg);
		        msg = addFillerLetter(msg);
		        cout << "Plain Text :- " << decryptMsg(msg);
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

int main()
{
	cout<<"************Hill Cipher Method************"<<endl;
    menu();
    return 0;
}
