/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#include <iostream>
#include <stdio.h>
#include <vector>
#include "node.h"
#include "parser.h"
#include "semantics.h"
#include "testTree.h"
#include "token.h"

using namespace std;

int main(int argc, char* argv[]) {
    FILE *file;
    char firstChar;
    node_t* root;
    vector<string> symbolTable;

    if (argc > 2) {
        printf("\nFatal: Improper usage\nUsage: frontEnd [file]\n\n");
        exit(EXIT_FAILURE);
    }
    else if (argc == 2) {
        // checking readability of file
        file = fopen(argv[1], "r");
        if (file == NULL) {
            printf("\nFatal: Invalid file name: %s\n\n", argv[1]);
            exit(EXIT_FAILURE);
        }
        // checking first character of file to ensure not empty
        if ((firstChar = fgetc(file)) == EOF) {
            printf("\nFatal: File is empty\n\n");
            exit(EXIT_FAILURE);
        }
        // if the file isn't empty, put the char back
        else 
            ungetc(firstChar, file);
    }
    else
        file = stdin;

    // call parser and check if it failed
    if ((root = parser(file)) == NULL) {
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // check the static semantics
    symbolTable = checkStatSem(root);

    // printing symbol table
    printf("\nSymbol Table:\n");
    for (auto str: symbolTable)
        printf("%s\n", str.c_str());
    printf("\n");

    // call printParseTree to print parse tree for debugging
    //printParseTree(root, 0);

    fclose(file);
    exit(EXIT_SUCCESS);
}
