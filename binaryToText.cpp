#include <iostream>
#include <string>
#include <sstream>
#include <bitset>

int main()
{
    std::string data;
    std::cin>>data;
    std::stringstream sstream(data);
    std::string output;
    while(sstream.good())
    {
        std::bitset<8> bits;
        sstream >> bits;
        char c = char(bits.to_ulong());
        output += c;
    }

    std::cout << output<<std::endl;

   return 0;
}
