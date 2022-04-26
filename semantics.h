/*
 *
 *  Project P3 - CS4280
 *  Author: Tony Urschler
 *  Date:   04/11/2022
 *
 * */

#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <vector>
#include "node.h"
#include "token.h"

using namespace std;

vector<string> checkStatSem(node_t *root);
void insert(string id);
bool verify(string id);

#endif
