#include<iostream>
#include <string>
#include <sstream>
#include <bitset>
using namespace std;
//    input text  input key   output text   16 keys arr   text's left  text's right  key's left   key's right
string text,       key,        cipherTex,    keys[16],    LPT,           RPT,          CKey="",       Dkey="";

// initial permutation table 
int IP[64]={
58,	50,	42,	34,	26,	18,	10,	2,	60,	52,	44,	36,	28,	20,	12,	4,
62,	54,	46,	38,	30,	22,	14,	6,	64,	56,	48,	40,	32,	24,	16,	8,
57,	49,	41,	33,	25,	17,	9,	1,	59,	51,	43,	35,	27,	19,	11,	3,
61,	53,	45,	37,	29,	21,	13,	5,	63,	55,	47,	39,	31,	23,	15,	7},
// first key table
Ckeys[28]={57,	49,	41,	33,	25,	17,	9,	1,	58,	50,	42,	34,	26,	18,
	   10,	2,	59,	51,	43,	35,	27,	19,	11,	3,      60,	52,	44,	36},
// second key table
Dkeys[28]={63,	55,	47,	39,	31,	23,	15,	7,	62,	54,	46,	38,	30,	22,
	   14,	6,	61,	53,	45,	37,	29,	21,	13,	5,	28,	20,	12,	4},
// CP table for key to 56->48
CPkeys[48]={14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10,
	  23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2,
	  41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48,
	  44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32},
// shift nums
n[16]={0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0},
// table EP for 32 to 48
EP[48]={32,	1,	2,	3,	4,	5,
	4,	5,	6,	7,	8,	9,
	8,	9,	10,	11,	12,	13,
	12,	13,	14,	15,	16,	17,
	16,	17,	18,	19,	20,	21,
	20,	21,	22,	23,	24,	25,
	24,	25,	26,	27,	28,	29,
	28,	29,	30,	31,	32,	1},
// S[i] blocks
S1[4][16]={
	{14,	4,	13,	1,	2,	15,	11,	8,	3,	10,	6,	12,	5,	9,	0,	7},	
	{0,	15,	7,	4,	14,	2,	13,	1,	10,	6,	12,	11,	9,	5,	3,	8},
	{4,	1,	14,	8,	13,	6,	2,	11,	15,	12,	9,	7,	3,	10,	5,	0},	
	{15,	12,	8,	2,	4,	9,	1,	7,	5,	11,	3,	14,	10,	0,	6,	13}
},

S2[4][16]={
	{15,	1,	8,	14,	6,	11,	3,	4,	9,	7,	2,	13,	12,	0,	5,	10},	
 	{3,	13,	4,	7,	15,	2,	8,	14,	12,	0,	1,	10,	6,	9,	11,	5},
 	{0,	14,	7,	11,	10,	4,	13,	1,	5,	8,	12,	6,	9,	3,	2,	15},	
	{13,	8,	10,	1,	3,	15,	4,	2,	11,	6,	7,	12,	0,	5,	14,	9}
},

S3[4][16]={
	{10,	0,	9,	14,	6,	3,	15,	5,	1,	13,	12,	7,	11,	4,	2,	8},	
	{13,	7,	0,	9,	3,	4,	6,	10,	2,	8,	5,	14,	12,	11,	15,	1},
	{13,	6,	4,	9,	8,	15,	3,	0,	11,	1,	2,	12,	5,	10,	14,	7},	
	{1,	10,	13,	0,	6,	9,	8,	7,	4,	15,	14,	3,	11,	5,	2,	12}
},

S4[4][16]={
	{7,	13,	14,	3,	0,	6,	9,	10,	1,	2,	8,	5,	11,	12,	4,	15},
	{13,	8,	11,	5,	6,	15,	0,	3,	4,	7,	2,	12,	1,	10,	14,	9},
	{10,	6,	9,	0,	12,	11,	7,	13,	15,	1,	3,	14,	5,	2,	8,	4},	
	{3,	15,	0,	6,	10,	1,	13,	8,	9,	4,	5,	11,	12,	7,	2,	14}
},

S5[4][16]={
	{2,	12,	4,	1,	7,	10,	11,	6,	8,	5,	3,	15,	13,	0,	14,	9},	
	{14,	11,	2,	12,	4,	7,	13,	1,	5,	0,	15,	10,	3,	9,	8,	6},
	{4,	2,	1,	11,	10,	13,	7,	8,	15,	9,	12,	5,	6,	3,	0,	14},	
	{11,	8,	12,	7,	1,	14,	2,	13,	6,	15,	0,	9,	10,	4,	5,	3}
},

S6[4][16]={
	{12,	1,	10,	15,	9,	2,	6,	8,	0,	13,	3,	4,	14,	7,	5,	11},	
	{10,	15,	4,	2,	7,	12,	9,	5,	6,	1,	13,	14,	0,	11,	3,	8},
	{9,	14,	15,	5,	2,	8,	12,	3,	7,	0,	4,	10,	1,	13,	11,	6},	
	{4,	3,	2,	12,	9,	5,	15,	10,	11,	14,	1,	7,	6,	0,	8,	13}
},

S7[4][16]={
	{4,	11,	2,	14,	15,	0,	8,	13,	3,	12,	9,	7,	5,	10,	6,	1},	
	{13,	0,	11,	7,	4,	9,	1,	10,	14,	3,	5,	12,	2,	15,	8,	6},
	{1,	4,	11,	13,	12,	3,	7,	14,	10,	15,	6,	8,	0,	5,	9,	2},	
	{6,	11,	13,	8,	1,	4,	10,	7,	9,	5,	0,	15,	14,	2,	3,	12}	
},

S8[4][16]={
	{13,	2,	8,	4,	6,	15,	11,	1,	10,	9,	3,	14,	5,	0,	12,	7},
	{1,	15,	13,	8,	10,	3,	7,	4,	12,	5,	6,	11,	0,	14,	9,	2},
	{7,	11,	4,	1,	9,	12,	14,	2,	0,	6,	10,	13,	15,	3,	5,	8},
	{2,	1,	14,	7,	4,	10,	8,	13,	15,	12,	9,	0,	3,	5,	6,	11}
},
// last permutation
LP[32]={
58, 50, 42, 34, 26, 18, 10, 2, 60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6, 64, 56, 48, 40, 32, 24, 16, 8
},
//final permutation
FP[64]={
40, 8, 48, 16, 56, 24, 64, 32, 39, 7, 47, 15, 55, 23, 63, 31,
38, 6, 46, 14, 54, 22, 62, 30, 37, 5, 45, 13, 53, 21, 61, 29,
36, 4, 44, 12, 52, 20, 60, 28, 35, 3, 43, 11, 51, 19, 59, 27,
34, 2, 42, 10, 50, 18, 58, 26, 33, 1, 41, 9,  49, 17, 57, 25
};


// generate keys C and D
void generateKeys(){
  // temp for key to binary
  string temp="";
  for(char& _char : key){
    temp+=bitset<8>(_char).to_string();
  }
  
  for(int i=0;i<28;i++){
    CKey+=temp[Ckeys[i]-1];
    Dkey+=temp[Dkeys[i]-1];
  }
  
  cout<<"\n\t\t\tYour key in binary:\n"<<temp<<" "<<temp.size()<<" bits\n\n";
  cout<<"\t\t\tDevide keys in 2 parts:\n"<<CKey<<" "<<CKey.size()<<" bits\n"<<Dkey<<" "<<Dkey.size()<<" bits\n\n";
  cout<<"__________________________________________________________________________\n\n";
}

// function for shift to n
void shift(int num){
  string first="", second="";
  for(int i=num+1;i<28;i++){
    first+=CKey[i];
    second+=Dkey[i];
  }
  for(int i=0;i<=num;i++){
    first+=CKey[i];
    second+=Dkey[i];
  }
  CKey=first;
  Dkey=second;
  //cout<<first<<"\n"<<second<<'\n';
}

// add 16 keys to array
void createKeys(){
  cout<<"\t\t\tGenerated 16 keys:\n";
  for(int i=0;i<16;i++){
    shift(n[i]);
    string s=CKey+Dkey, temp="";
    for(int j=0;j<48;j++){
      temp+=s[CPkeys[j]-1];
    }
    
    cout<<i+1<<"-key: "<<temp<<" "<<temp.size()<<" bits"<<"\n";
    keys[i]=temp;
  }
}

// convert binary to string function
// string str=bitset<8>(binstring).to_string();

// first permutation
void permutation(){
  string temp="", ipText="";
  
  for (char& _char : text) {
    temp+=bitset<8>(_char).to_string();
  }
  
  cout<<"__________________________________________________________________________\n\t\t\tText in binary:\n";
  cout<<temp<<" "<<temp.size()<<" bits"<<endl;
  
  for(int i=0;i<64;++i){
    ipText+=temp[IP[i]-1];
  }
  cout<<"__________________________________________________________________________\n\t\t\tPermutation:\n";
  cout<<ipText<<" "<<ipText.size()<<" bits\n";
  
  LPT=ipText.substr(0, 32);
  RPT=ipText.substr(32, 32);
  cout<<"__________________________________________________________________________\n\t\tDevide left and right parts:\nLeft: ";
  cout<<LPT<<' '<<LPT.size()<<" bits\nRight: "<<RPT<<' '<<RPT.size()<<" bits";
}

// EP function for RPT 32->48
string funEP(){
  string result="";
  for(int i=0;i<48;i++){
    result+=RPT[EP[i]-1];
  }
  
  //cout<<"\n\n\n"<<result<<' '<<result.size()<<endl;
  return result;
}

// XOR function key^s
string funXOR(string s, int l){
  string key=keys[l], res="";
  for(int i=0;i<48;i++){
    int m=(s[i]-'0')^(key[i]-'0');
    res+=to_string(m);
  }
  
  return res;
}

//XOR function for 32 bit
string fun32XOR(string left, string right){
  string result="";
  for(int i=0;i<32;i++){
    int m=(left[i]-'0')^(right[i]-'0');
    result+=to_string(m);
  }
  
  return result;
}

// 16 times cipher
void cipher(int index){
// get duplicate RPT
  string duplicate=RPT;
  
  // function EP 32 to 48
  string temp=funEP();
  
  // key[i] XOR temp
  temp=funXOR(temp, index);
  //cout<<"\nResult: "<<temp<<" "<<temp.size();
  
// devide temp in 8 blocks with 6 bits
  // set block B
  string B[8], Stmp[8];
  
  //fill block B
  for(int i=0, j=0;i<8;i++, j+=6){
    string tmp=temp.substr(j, 6);
    B[i]=tmp;
  }
  //cout<<index+1<<"-cicle "<<temp<<" "<<temp.size()<<" bits\n";
  /*for(int i=0;i<8;i++){
    cout<<B[i]<<" ";
  } */
  
  
  // fill from Sblock table
  // convert to dec and find element from S blocks then sum all Stmp blocks, last permutation, XOR
  for(int i=0;i<8;i++){
    string tmp=B[i], str="";
    //cout<<"tmp="<<tmp<<endl;
    str+=tmp[0];
    str+=tmp[5];
    tmp=tmp.substr(1, 4);
    //cout<<"str="<<str<<" "<<tmp<<"\n";
    bitset<32> first(str);
    bitset<32> second(tmp);
    int row=first.to_ulong(), column=second.to_ulong();
    //cout<<"row:"<<row<<" column:"<<column<<endl;
    int stmp;
    if(i==0)
      stmp=S1[row][column];
    else if(i==1)
      stmp=S2[row][column];
    else if(i==2)
      stmp=S3[row][column];
    else if(i==3)
      stmp=S4[row][column];
    else if(i==4)
      stmp=S5[row][column];
    else if(i==5)
      stmp=S6[row][column];
    else if(i==6)
      stmp=S7[row][column];
    else if(i==7)
      stmp=S8[row][column];
    //cout<<stmp<<" ";
    //Stmp[i]=stmp;
    Stmp[i]=bitset<4>(stmp).to_string();  
  }
  temp="";
  for(int j=0;j<8;j++){
    temp+=Stmp[j];
  }
  
  if(index!=15){
    RPT=fun32XOR(LPT, temp);
    LPT=duplicate;
  }
  
  cout<<"\t\t\t"<<index+1<<"-cicle:\n";
  cout<<"Right part: "<<RPT<<' '<<RPT.size()<<" bits\nLeft part: "<<LPT<<' '<<LPT.size()<<" bits\n";
  
  //cout<<temp<<" "<<temp.size();
  
}

string finalPermutation(){
  string all=LPT+RPT, result="";
  for(int i=0;i<64;i++){
    result+=all[FP[i]-1];
  }
  
  return result;
}

string convertToText(string data){
    //std::string data;
    //std::cin>>data;
    stringstream sstream(data);
    string output;
    while(sstream.good())
    {
        bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

   return output;
}

int main(){
  cout<<"##########################################################################\n";
  cout<<"                        DES algorithm, happy cipher ;)                    \n";
  cout<<"##########################################################################\n\n";
  cout<<"Input the text for cipher: \n";
  getline(cin, text);
  cout<<"\nInput the key for cipher (8 characters):\n";
  cin>>key;
  key=key.substr(0, 8);
  cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
  permutation();
  cout<<"\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
  generateKeys();
  createKeys();
  cout<<"__________________________________________________________________________\n\n";
  for(int i=0;i<16;i++){
    cipher(i);
  }
  cout<<"\n__________________________________________________________________________\n\n";
  
  string ciphertext=finalPermutation();
  cout<<"\t\t\tFinal permutation:\n"<<ciphertext<<" "<<ciphertext.size()<<" bits\n";
  ciphertext=convertToText(ciphertext);
  cout<<"\n__________________________________________________________________________\n\n\t\t\tResult:\n";
  cout<<ciphertext<<endl;
  
  return 0;
  

}
