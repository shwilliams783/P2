#include <iostream>
#include <list>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <string>
#include "token.h"
#include "scanner.h"
#include "parser.h"
#include "node.h"

extern FILE *infp;
extern token tk;
static int currentDepth = 0;

static const int BUFFER = 80;
static char errmsg[BUFFER];

node_t* parser()
{
	node_t* root = new node_t;
	root->depth = currentDepth;
	
	std::cout<<"parser()"<<std::endl; /* Remove after debugging */
	tk = scanner();
	root = program();
	std::cout<<"Program complete, expecting EOFTK."<<std::endl; /* Remove after debugging */
	if(tk.id == EOFTK)
	{
		currentDepth--;
		return root;
	}
	else
		parseError(32, tk.line);
}

node_t* program()
{
	currentDepth++;
	node_t* p = genNode(progND, currentDepth);
	
	std::cout<<"program()"<<std::endl; /* Remove after debugging */
	if(tk.id == progTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = vars();
		p->child1 = block();
		currentDepth--;
		return p;
	}
	else
		parseError(9, tk.line);
}

node_t* block()
{
	currentDepth++;
	node_t* p = genNode(blocND, currentDepth);
	
	std::cout<<"block()"<<std::endl; /* Remove after debugging */
	if(tk.id == starTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = vars();
		p->child1 = stats();
		if(tk.id == stopTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			currentDepth--;
			return p;
		}
		else
			parseError(2, tk.line);
	}
	else
		parseError(7, tk.line);
}

node_t* vars()
{
	currentDepth++;
	node_t* p = genNode(varsND, currentDepth);
	
	std::cout<<"vars()"<<std::endl; /* Remove after debugging */
	if(tk.id == varTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		if(tk.id == IDTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			p->tokens[0] = tk;
			tk = scanner();
			if(tk.id == eqTK)
			{
				std::cout<<tk.name<< std::endl; /* Remove after debugging */
				tk = scanner();
				if(tk.id == IntTK)
				{
					std::cout<<tk.name<< std::endl; /* Remove after debugging */
					p->tokens[1] = tk;
					tk = scanner();
					p->child0 = mvars();
					currentDepth--;
					return p;
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
		return p;
}

node_t* mvars()
{
	currentDepth++;
	node_t* p = genNode(mvarND, currentDepth);
	
	std::cout<<"mvars()"<<std::endl; /* Remove after debugging */
	if(tk.id == pdTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		currentDepth--;
		return p;		
	}
	else if(tk.id = colTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		if(tk.id == IDTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			p->tokens[0] = tk;
			tk = scanner();
			p->child0 = mvars();
			currentDepth--;
			return p;
		}
		else
			parseError(1, tk.line);
	}
	else
		parseError(17, tk.line);
}

node_t* expr()
{
	currentDepth++;
	node_t* p = genNode(exprND, currentDepth);
	
	std::cout<<"expr()"<<std::endl; /* Remove after debugging */
	p->child0 = M();
	if(tk.id == plTK)
	{
		p->type = addND;
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child1 = expr();
		currentDepth--;
		return p;
	}
	else if(tk.id == miTK)
	{
		p->type = subND;
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child1 = expr();
		currentDepth--;
		return p;
	}
	else if(tk.id == fsTK)
	{
		p->type = divND;
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child1 = expr();
		currentDepth--;
		return p;
	}
	else if(tk.id == stTK)
	{
		p->type = multND;
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child1 = expr();
		currentDepth--;
		return p;
	}
	else
	{
		currentDepth--;
		return p;
	}
}

node_t* M()
{
	currentDepth++;
	node_t* p = genNode(MND, currentDepth);
	
	std::cout<<"M()"<<std::endl; /* Remove after debugging */
	if(tk.id == modTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = M();
		currentDepth--;
		return p;
	}
	else
	{
		p->child0 = R();
		currentDepth--;
		return p;
	}
}

node_t* R()
{
	currentDepth++;
	node_t* p = genNode(RND, currentDepth);
	
	std::cout<<"R()"<<std::endl; /* Remove after debugging */
	if(tk.id == lpTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = expr();
		if(tk.id == rpTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			currentDepth--;
			return p;
		}
		else
			parseError(25, tk.line);
	}
	else if(tk.id == IDTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		p->tokens[0] = tk;
		tk = scanner();
		currentDepth--;
		return p;
	}
	else if(tk.id == IntTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		p->tokens[0] = tk;
		tk = scanner();
		currentDepth--;
		return p;
	}
	else
		parseError(0, tk.line);
}

node_t* stats()
{
	currentDepth++;
	node_t* p = genNode(stsND, currentDepth);
	
	std::cout<<"stats()"<<std::endl; /* Remove after debugging */
	p->child0 = stat();
	p->child1 = mstat();
	currentDepth--;
	return p;
}

node_t* mstat()
{
	currentDepth++;
	node_t* p = genNode(mstND, currentDepth);
	
	std::cout<<"mstat()"<<std::endl; /* Remove after debugging */
	if(tk.id == readTK || tk.id == prntTK || tk.id == starTK || tk.id == iffTK || tk.id == iterTK || tk.id == letTK)
	{
		p->child0 = stat();
		p->child1 = mstat();
		currentDepth--;
		return p;
	}
	else
	{
		currentDepth--;
		return p;
	}
}

node_t* stat()
{
	currentDepth++;
	node_t* p = genNode(statND, currentDepth);
	
	std::cout<<"stat()"<<std::endl; /* Remove after debugging */
	if(tk.id == readTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = in();
		currentDepth--;
		return p;
	}
	else if(tk.id == prntTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = out();
		currentDepth--;
		return p;
	}
	else if(tk.id == starTK)
	{
		p->child0 = block();
		currentDepth--;
		return p;
	}
	else if(tk.id == iffTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = ifFunc();
		currentDepth--;
		return p;
	}
	else if(tk.id == iterTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = loop();
		currentDepth--;
		return p;
	}
	else if(tk.id == letTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = assign();
		currentDepth--;
		return p;
	}
	else
		parseError(13, tk.line);
	
}

node_t* in()
{
	currentDepth++;
	node_t* p = genNode(inND, currentDepth);
	
	std::cout<<"in()"<<std::endl; /* Remove after debugging */
	if(tk.id == IDTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		p->tokens[0] = tk;
		tk = scanner();
		if(tk.id == pdTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			currentDepth--;
			return p;
		}
		else
			parseError(23, tk.line);
	}
	else
		parseError(1, tk.line);
}

node_t* out()
{
	currentDepth++;
	node_t* p = genNode(outND, currentDepth);
	
	std::cout<<"out()"<<std::endl; /* Remove after debugging */
	p->child0 = expr();
	if(tk.id == pdTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		currentDepth--;
		return p;
	}
	else
		parseError(23, tk.line);
}

node_t* ifFunc()
{
	currentDepth++;
	node_t* p = genNode(iffND, currentDepth);
	
	std::cout<<"ifFunc()"<<std::endl; /* Remove after debugging */
	if(tk.id == lpTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = expr();
		p->child1 = RO();
		p->child2 = expr();
		if(tk.id == rpTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			p->child3 = stat();
			currentDepth--;
			return p;
		}
		else
			parseError(25, tk.line);
	}
	else
		parseError(24, tk.line);
}

node_t* loop()
{
	currentDepth++;
	node_t* p = genNode(loopND, currentDepth);
	
	std::cout<<"loop()"<<std::endl; /* Remove after debugging */
	if(tk.id == lpTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		p->child0 = expr();
		p->child1 = RO();
		p->child2 = expr();
		if(tk.id == rpTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			p->child3 = stat();
			currentDepth--;
			return p;
		}
		else
			parseError(25, tk.line);
	}
	else
		parseError(24, tk.line);
}

node_t* assign()
{
	currentDepth++;
	node_t* p = genNode(asgnND, currentDepth);
	
	std::cout<<"assign()"<<std::endl; /* Remove after debugging */
	if(tk.id == IDTK)
	{
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		p->tokens[0] = tk;
		tk = scanner();
		if(tk.id == eqTK)
		{
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			p->child0 = expr();
			if(tk.id == pdTK)
			{
				std::cout<<tk.name<< std::endl; /* Remove after debugging */
				tk = scanner();
				currentDepth--;
				return p;
			}
			else
				parseError(23, tk.line);
		}
		else
			parseError(14, tk.line);
	}
	else
		parseError(1, tk.line);
}

node_t* RO()
{
	currentDepth++;
	node_t* p = genNode(ROND, currentDepth);
	
	std::cout<<"RO()"<<std::endl; /* Remove after debugging */
	if(tk.id == ltTK)
	{
		p->type = ltND;
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		if(tk.id == ltTK)
		{
			p->type = leND;
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			currentDepth--;
			return p;
		}
		else
		{
			currentDepth--;
			return p;
		}
	}
	else if(tk.id == gtTK)
	{
		p->type = gtND;
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		if(tk.id == gtTK)
		{
			p->type = geND;
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			currentDepth--;
			return p;
		}
		else
		{
			currentDepth--;
			return p;
		}
	}
	else if(tk.id == eqTK)
	{
		p->type = eqND;
		std::cout<<tk.name<< std::endl; /* Remove after debugging */
		tk = scanner();
		if(tk.id == eqTK)
		{
			p->type = eqeqND;
			std::cout<<tk.name<< std::endl; /* Remove after debugging */
			tk = scanner();
			currentDepth--;
			return p;
		}
		else
		{
			currentDepth--;
			return p;
		}
	}
	else
		parseError(14, tk.line);
}

node_t* genNode(int type, int depth)
{
	std::cout<<"genNode "<<type<<" "<<depth<<std::endl;
	node_t* node = new node_t;
	node->type = (nodeType)type;
	node->depth = depth;
	return node;
}

void parseError(int errCode, int line)
{
	snprintf(errmsg, sizeof(errmsg), "Line %d: ERROR MESSAGE PLACE HOLDER #%d.", line, errCode);
	perror(errmsg);
	exit(errCode);
}