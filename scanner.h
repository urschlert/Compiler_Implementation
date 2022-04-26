/*
 *
 * Project P3 - CS4280
 * Author:  Tony Urschler
 * Date:    04/11/2022
 *
 * */

#ifndef SCANNER_H
#define SCANNER_H

#include "token.h"

token_t scanner(FILE *file, char lookAhead, int line);
int getCharIndex(char);

#endif
