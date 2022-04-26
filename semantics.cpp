/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#include <algorithm>
#include <ctype.h>
#include <iostream>
#include <vector>
#include <stdio.h>
#include "node.h"
#include "semantics.h"
#include "token.h"

using namespace std;

static vector<string> symbolTable;

/*
 *  Function:   checkStatSem
 *  Parameters: node_t
 *  Desc:       Takes the root of a tree and systematically ensures that
 *              Identifiers are properly used and defined
 * */
vector<string> checkStatSem(node_t *root) {
    if (root == NULL)
        return symbolTable;
    
    // if label S, store ID
    if (root->label == "S") {
        // no need to verify, it will always be the first declared
        insert(root->child2->token.tokenInstance);
        
        // check the second declared variable
        if (verify(root->child4->token.tokenInstance)) {
            printf("ERROR: Line %d redefinition of variable \"%s\".\n",
                root->child4->token.lineNumber,
                root->child4->token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        insert(root->child4->token.tokenInstance);
    }

    // if label A, store ID
    else if (root->label == "A") {
        // ensure not previously declared
        if (verify(root->child2->token.tokenInstance)) {
            printf("ERROR: Line %d redefinition of variable \"%s\".\n",
                root->child2->token.lineNumber,
                root->child2->token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
        insert(root->child2->token.tokenInstance);
    }
    
    // check if it's a ID token, and if it's been declared
    else if (root->label == "" && root->token.tokenID == IDTkn) {
        if (!verify(root->token.tokenInstance)) {
            printf("ERROR: Line %d using undefined variable \"%s\".\n",
                root->token.lineNumber,
                root->token.tokenInstance.c_str());
            exit(EXIT_FAILURE);
        }
    }

    // continue to traverse through the rest of the tree
    checkStatSem(root->child1);
    checkStatSem(root->child2);
    checkStatSem(root->child3);
    checkStatSem(root->child4);
    checkStatSem(root->child5);
    checkStatSem(root->child6);
    checkStatSem(root->child7);

    return symbolTable;
}

/*
 *  Function:   insert
 *  Parameters: string
 *  Desc:       Inserts a string into the symbol table. Also checks if
 *              insertion keeps table in alphabetical order.
 * */
void insert(string id) {
    string last = "";
    string upper = id;
    
    // check if there's anything in the table
    if (!symbolTable.empty()) {
        last = symbolTable.back();

        // make characters upper case for comparison
        for (auto &c: last)
            c = toupper(c);
        for (auto &c: upper)
            c = toupper(c);

        // loop through and determine if alphabetical
        for (int i = 0; i < (int)last.length() && i < (int)upper.length(); i++) {
            if (upper[i] == last[i])
                continue;
            else if (upper[i] > last[i])
                break;
            else {
                printf("ERROR: Declarations not in alphabetical order.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    
    symbolTable.push_back(id);
}

/*
 *  Function:   verify
 *  Parameters: string
 *  Desc:       Determines if a given string is in the symbol table. If
 *              it is, then it returns true, else it return false.
 * */
bool verify(string id) {
    if (find(symbolTable.begin(), symbolTable.end(), id) != symbolTable.end())
        return true;
    else
        return false;
}
