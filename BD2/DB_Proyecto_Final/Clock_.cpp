#include <iostream>
#include <vector>
#include <string>
#include "Buffer_manager.h"
using namespace std;
// A D B F E C A H I D L B C J K M E A C M H I G
int main(){
    string in;
    int n=4;
    getline(cin,in);
    vector<char> input;
    for(unsigned int i=0;i<in.length();i++)
        if(in[i]!=' ') input.push_back(in[i]);
    Bufferpool<char>* BP = new Bufferpool<char>(n);
    for(unsigned int i=0;i<input.size();i++){
        BP->_CLOCK(input[i]);
    }
}