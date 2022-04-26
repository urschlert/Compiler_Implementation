/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#ifndef TESTSCANNER_H
#define TESTSCANNER_H

#include "node.h"
#include "token.h"

node_t* parser(FILE*);
bool keywordValid(std::string);
char removeWhiteSpace(FILE*);
node_t* S();
node_t* R();
node_t* E();
node_t* A();
node_t* B();
node_t* C();
node_t* D();
node_t* F();
node_t* G();
node_t* T();
node_t* V();
node_t* H();
node_t* J();
node_t* K();
node_t* L();
node_t* W();
node_t* Z();

#endif
