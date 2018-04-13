#ifndef PARSER_H
#define PARSER_H

#include "token.h"

/* Function prototypes */
void parser();
void program();
void block();
void vars();
void mvars();
void expr();
void M();
void R();
void stats();
void mstat();
void stat();
void in();
void out();
void ifFunc();
void loop();
void assign();
void RO();
void parseError(int, int);

#endif