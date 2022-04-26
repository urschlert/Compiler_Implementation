/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#ifndef TOKEN_H
#define TOKEN_H

enum token { EOFTkn, IDTkn, KeyTkn, OpTkn, NumTkn, CommTkn };

struct token_t {
    token tokenID;
    std::string tokenInstance;
    int lineNumber;
   
    /*
     *  Function:   Constructor for token_t struct
     *  Parameters: token, string, int
     *  Desc:       Creates a token_t token with the given parameters
     * */
    token_t(token newTkn, std::string tknStr, int line) {
        tokenID = newTkn;
        tokenInstance = tknStr;
        lineNumber = line;
    }
    
    /*
     *  Function:   Default constuctor for token_t struct
     *  Parameters: None
     *  Desc:       Creates an empty token_t
     * */
    token_t() {}
};

#endif
