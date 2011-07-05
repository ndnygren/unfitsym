#ifndef NN_EXPRMETRIC_H
#define NN_EXPRMETRIC_H

#include "../parse/nodes/eqnNode.h"

class exprMetric
{
	public:
	int score(const eqnNode*  node) const
	{
		return node->str().length();	
	}
};

#endif
