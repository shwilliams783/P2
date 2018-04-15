#include <iostream>
#include <list>
#include <stdio.h>
#include <cstring>
#include <stdlib.h>
#include <string>
#include "node.h"
#include "testTree.h"

/* 	 nodeType  					   {0,	1,	2,	3,
									4,	5,	6,	7, 8,
									9,	10,	11,	12,
									13,	14,	15, 16,
									17,	18,	19, 20, 21,
									22, 23,	24, 25};
*/

static std::string nodeNames[26] = {"<program>", "<block>", "<vars>", "<mvars>",
									"<expr>", "<M>", "<R>", "<stats>", "<stat>",
									"<mStat>", "<in>", "<out>", "<if>",
									"<loop>", "<assign>", "<RO>", "<add>",
									"<sub>", "<div>", "<mult>",	"<lt>", "<le>",
									"<gt>", "<ge>", "<eq>",	"<eqeq>"};


/*	traversePreorder() outputs the node types and tokens contained in each node of the tree
	in the order: root (self), child0, child1, child2, child3.*/
void traversePreorder(node_t* root)
{
	int i;
		
	/* Resolve the root */
	for(i = 0; i < root->depth; i++)
	{
		std::cout<<"  ";
	}
	std::cout<<nodeNames[root->type]<<" ";
	if(root->tokens[0].str.compare("NULL") != 0)
	{
		std::cout<<"tokens: "<<root->tokens[0].str;
	}
	if(root->tokens[1].str.compare("NULL") != 0)
	{
		std::cout<<" "<<root->tokens[1].str;
	}
	if(root->tokens[2].str.compare("NULL") != 0)
	{
		std::cout<<" "<<root->tokens[2].str;
	}
	if(root->tokens[3].str.compare("NULL") != 0)
	{
		std::cout<<" "<<root->tokens[3].str;
	}
	std::cout<<std::endl;
	
	/* Resolve children, left to right */
	
	/* Resolve child0 */
	if(root->child0 != NULL)
	{
		traversePreorder(root->child0);
	}
	/* Resolve child1 */
	if(root->child1 != NULL)
	{
		traversePreorder(root->child1);
	}
	/* Resolve child2 */
	if(root->child2 != NULL)
	{
		traversePreorder(root->child2);
	}
	/* Resolve child3 */
	if(root->child3 != NULL)
	{
		traversePreorder(root->child3);
	}
}