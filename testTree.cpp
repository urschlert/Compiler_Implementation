/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#include <iostream>
#include <stdio.h>
#include "testTree.h"
#include "node.h"
#include "token.h"

using namespace std;

string tokens[] = { 
    "EOF", "Identifier", "Keyword", "Operator", "Number" 
};

/*
 *  Function:   printParseTree
 *  Parameters: node_t*, int
 *  Returns:    void
 *  Desc:       Writes a given parse tree to console using
 *              preorder traversal techniques.
 * */

void printParseTree(node_t *root, int level) {
    string tokStr = "";
    
    if (root == NULL)
        return;
    
    if (root->label != "") {
        printf("%*s%s\n",
            level * 2, "", root->label.c_str());
    }
    else {
        if (root->token.tokenID == IDTkn ||
            root->token.tokenID == OpTkn ||
            root->token.tokenID == NumTkn) {
            printf("%*s%s %s\n",
                level * 2, "", tokens[root->token.tokenID].c_str(),
                root->token.tokenInstance.c_str());
        }
        else {
            printf("%*s%s\n",
                level * 2, "", root->token.tokenInstance.c_str());
        }
    }
    
    // recusively call other children
    printParseTree(root->child1, level + 1);
    printParseTree(root->child2, level + 1);
    printParseTree(root->child3, level + 1);
    printParseTree(root->child4, level + 1);
    printParseTree(root->child5, level + 1);
    printParseTree(root->child6, level + 1);
    printParseTree(root->child7, level + 1);
}
