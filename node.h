/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#ifndef NODE_H
#define NODE_H

#include "token.h"

struct node_t {

    // label represents which rule created the node
    std::string label = "";

    // token for if there's a token here
    token_t token;

    // child nodes for parse tree
    node_t* child1;
    node_t* child2;
    node_t* child3;
    node_t* child4;
    node_t* child5;
    node_t* child6;
    node_t* child7;

    /*
     *  Function:   Constructor for node_t struct
     *  Parameters: std::string, token_t
     *  Desc:       Creates a node_t node with the given parameters
     * */
    node_t(std::string newLabel, token_t newToken) {
        label = newLabel;
        token = newToken;
    }

    /*
     *  Function:   Default constructor for node_t struct
     *  Parameters: None
     *  Desc:       Creates an empty node_t
     * */
    node_t() {}
};


#endif
