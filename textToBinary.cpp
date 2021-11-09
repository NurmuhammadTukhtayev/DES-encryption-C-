#include<iostream>
#include<bitset>
#include<algorithm>
using namespace std;

int main(){
  /* int k=15;
  string t=bitset<8>(k).to_string();
  cout<<(k<<2);
  cout<<'\n'<<t;
  t=bitset<8>(k<<2).to_string();
  cout<<'\n'<<t<<endl; */
  char s;
  cin>>s;
  bitset<8> b(s);
  int dec=b.to_ulong();
  cout<<dec;
  return 0;
}
