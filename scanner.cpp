/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include "scanner.h"
#include "token.h"

using namespace std;

const int FSASIZE = 9;
static int fsaTable[][FSASIZE] = {
    {6, 1, 3, 5, -1, 4, 7, 1001, 0},
    {2, 2, 2, -2, -2, -2, -2, -2, -2},
    {2, 2, 2, 1002, 1002, 1002, 1002, 1002, 1002},
    {1003, 3, 1003, 1003, 1003, 1003, 1003, 1003, 1003},
    {1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004, 1004},
    {-1, -1, -1, 4, 4, -1, -1, -1, -1},
    {6, 1005, 1005, 1005, 1005, 1005, 1005, 1005, 1005},
    {7, 7, 7, 7, 7, 7, 8, 8, 7 },
    {1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006, 1006}
};
static token finalStates[] = {
    EOFTkn, IDTkn, KeyTkn, OpTkn, NumTkn, CommTkn
};
static string errorTable[] = {
    "Invalid Operator", 
    "ID must have two or more characters", 
    "Invalid Character"
};

/*
 *  Function:   scanner
 *  Parameters: FILE*, char, int
 *  Returns:    token_t
 *  Desc:       Reads from the given file pointer, char by char, until
 *              a final state is met or an error occurs. It then either
 *              returns the token, or outputs the error.
 * */
token_t scanner(FILE *file, char lookAhead, int line) {
    string word = "";
    string errStmt = "";
    token_t token;
    int state = fsaTable[0][getCharIndex(lookAhead)];
    
    // loop until a final state occurs
    while (state < 1000) {
        // process errors
        if (state < 0) {
            // get proper error statement from table
            errStmt = errorTable[-(state + 1)];
            printf("SCANNER ERROR: Line %d: %s \"%s\"\n", 
                line, errStmt.c_str(), word.c_str());
            exit(EXIT_FAILURE);
        }
        // add character to word, get next char, and determine state
        word = word + lookAhead;       
        lookAhead = fgetc(file);
        state = fsaTable[state][getCharIndex(lookAhead)];
    }
    // put the last char back and create token
    ungetc(lookAhead, file);

    token = token_t(finalStates[state % 1000 - 1], word, line);
    
    return token;
}

/*
 *  Function:   getCharIndex
 *  Parameters: char
 *  Returns:    int
 *  Desc:       Determines what type of character the given char is.
 *              Then returns the corresponding numerical value. Returns
 *              -3 if invalid.
 * */
int getCharIndex(char checkChar) {
    if (isdigit(checkChar))
        return 0;
    else if (islower(checkChar))
        return 1;
    else if (isupper(checkChar))
        return 2;
    else if (checkChar == '<')
        return 3;
    else if (checkChar == '-')
        return 4;
    else if (checkChar == '&' || checkChar == '+'
            || checkChar == '/' || checkChar == '%'
            || checkChar == '.' || checkChar == '{'
            || checkChar == '}')
        return 5;
    else if (checkChar == '*')
        return 6;
    else if (checkChar == EOF)
        return 7;
    else if (isspace(checkChar))
        return 8;
    else
        return -3;
}
