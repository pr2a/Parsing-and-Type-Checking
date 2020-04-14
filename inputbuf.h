//
//  inputbuf.h
//  CSE340_Project4
//
//  Created by Priya Ganguly on 4/10/20.
//  Copyright © 2020 idk. All rights reserved.
//

#ifndef inputbuf_h
#define inputbuf_h

#include <stdio.h>
#include <string>

class InputBuffer {
public:
    void GetChar(char&);
    char UngetChar(char);
    std::string UngetString(std::string);
    bool EndOfInput();

private:
    std::vector<char> input_buffer;
};



#endif /* inputbuf_h */
