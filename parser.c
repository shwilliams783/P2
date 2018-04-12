#include <iostream>
#include <list>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <string>
#include "token.h"
#include "scanner.h"
#include "parser.h"

extern FILE *infp;
extern token tk;

static const int BUFFER = 80;
static char errmsg[BUFFER];

void parser()
{
	std::cout<<"parser()"<<std::endl; /* Remove after debugging */
	tk = scanner();
	program();
	std::cout<<"Program complete, expecting EOFTK."<<std::endl; /* Remove after debugging */
	if(tk.id == EOFTK);
	else
		parseError(32, tk.line);
	return;
}

void program()
{
	std::cout<<"program()"<<std::endl; /* Remove after debugging */
	if(tk.id == progTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		vars();
		block();
		return;
	}
	else
		parseError(9, tk.line);
}

void block()
{
	std::cout<<"block()"<<std::endl; /* Remove after debugging */
	if(tk.id == starTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		vars();
		//stats();
		if(tk.id == stopTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			return;
		}
		else
			parseError(2, tk.line);
	}
	else
		parseError(7, tk.line);
}

void vars()
{
	std::cout<<"vars()"<<std::endl; /* Remove after debugging */
	if(tk.id == varTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		if(tk.id == IDTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			if(tk.id == eqTK)
			{
				std::cout<<tk.name<< std::endl; /* Remove after debugging */
				tk = scanner();
				if(tk.id == IntTK)
				{
					std::cout<<tk.name<< std::endl; /* Remove after debugging */
					tk = scanner();
					mvars();
					return;
				}
				else
					parseError(0, tk.line);
			}
			else
				parseError(14, tk.line);
		}
		else
			parseError(1, tk.line);
	}
	else
		return;
}

void mvars()
{
	std::cout<<"mvars()"<<std::endl; /* Remove after debugging */
	if(tk.id == pdTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		return;		
	}
	else if(tk.id = colTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		if(tk.id == IDTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			mvars();
			return;
		}
		else
			parseError(1, tk.line);
	}
	else
	{
		parseError(17, tk.line);
	}
}

void parseError(int errCode, int line)
{
	snprintf(errmsg, sizeof(errmsg), "Line %d: ERROR MESSAGE PLACE HOLDER #%d.", line, errCode);
	perror(errmsg);
	exit(errCode);
}