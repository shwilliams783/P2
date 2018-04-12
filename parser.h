#ifndef PARSER_H
#define PARSER_H

#include "token.h"

/* Function prototypes */
void parser();
void program();
void block();
void vars();
void mvars();
void stats();
void stat();
void parseError(int, int);

#endif