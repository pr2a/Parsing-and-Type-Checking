//
//  inputbuf.cc
//  CSE340_Project4
//
//  Created by Priya Ganguly on 4/10/20.
//  Copyright © 2020 idk. All rights reserved.
//

#include "inputbuf.h"

#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cstdio>

using namespace std;

bool InputBuffer::EndOfInput(){
    if(!input_buffer.empty())
        return false;
    else
        return cin.eof();
}

bool InputBuffer::UngetChar(char c){
    if(c != EOF)
        input_buffer.push_back(c);
    return c;
}

bool InputBuffer::GetChar(char &c){
    if(!input_buffer.empty()){
        c = input_buffer.back();
        input_buffer.pop_back();
    }
    else{
        cin.get(c);
    }
}

string InputBuffer::UngetString(string s){
    for (int i = 0; i < s.size(); i++)
        input_buffer.push_back(s[s.size()-i-1]);
    return s;
}
