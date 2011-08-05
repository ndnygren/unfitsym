/* unfitsym - framework for symbolic computation
* Copyright (C) 2011 Nick Nygren
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>. */
#ifndef NN_GENALT_H
#define NN_GENALT_H

#include <vector>
#include "../../parse/nodes/eqnNode.h"
#include "../../parse/nodes/sumNode.h"
#include "../../parse/nodes/subNode.h"
#include "../../parse/nodes/prodNode.h"
#include "../../parse/nodes/numNode.h"
#include "../../parse/nodes/varNode.h"
#include "../../parse/nodes/fracNode.h"
#include "../../parse/nodes/negNode.h"
#include "../../parse/nodes/hatNode.h"
#include "../../parse/nodes/derivNode.h"
#include "../../parse/nodes/intNode.h"
#include "../../parse/nodes/lnNode.h"
#include "../../parse/nodes/sineNode.h"
#include "../../parse/nodes/cosineNode.h"
#include "../../parse/nodes/nodeTypes.h"

class alterExpression
{
	protected:
	// expression manipulations specific to the root operator 
	//	of the expression tree
	static std::vector<eqnNode*> sumCand(sumNode* input);
	static std::vector<eqnNode*> subCand(subNode* input);
	static std::vector<eqnNode*> prodCand(prodNode* input);
	static std::vector<eqnNode*> fracCand(fracNode* input);
	static std::vector<eqnNode*> intCand(intNode* input);
	static std::vector<eqnNode*> lnCand(lnNode* input);
	static std::vector<eqnNode*> cosineCand(cosineNode* input);
	static std::vector<eqnNode*> sineCand(sineNode* input);
	static std::vector<eqnNode*> derivCand(derivNode* input);
	static std::vector<eqnNode*> negCand(negNode* input);
	static std::vector<eqnNode*> hatCand(hatNode* input);

	/*
	 * eqnNode* attemptStrip(intNode* input);
	 *
	 * solves the integral in such a way that the result contains to 
	 *	remaining integrals, but is not specific to either bounded 
	 *	or unbounded integrals
	 */
	static eqnNode* attemptStrip(intNode* input);

	/*
	 * vector<eqnNode*> getAssocVector(binOpNode* input)
	 *
	 * returns the statement in a vector form, representing the general 
	 *	associative form.
	 */
	static std::vector<eqnNode*> getAssocVector(binOpNode* input);

	// combines a list of expressions into a product of expressions
	static eqnNode* buildProduct(std::vector<eqnNode*>& list);

	// combines a list of expressions into a sum of expressions
	static eqnNode* buildSum(std::vector<eqnNode*>& list);


	// sorted/grouped assoc vector construction
	static void pushToBrk(std::vector<std::pair<eqnNode*, std::vector<eqnNode*> > >& brklist, eqnNode* base, eqnNode* arg);

	/*
	 * eqnNode* sumSimplify(sumNode* input)
	 *
	 * rapid simplification of sums, by general associativity and comutivity
	 */
	static eqnNode* sumSimplify(sumNode* input);

	/*
	 * eqnNode* prodSimplify(sumNode* input)
	 *
	 * rapid simplification of products, by general associativity and comutivity
	 */
	static eqnNode* prodSimplify(prodNode* input);

	public:
	// creates a vector copy, allocating new memory
	static void copyCand(const std::vector<eqnNode*>& from, std::vector<eqnNode*>& to); 

	// frees all memory in the vector
	static void freeCand(std::vector<eqnNode*>& list);

	// calls searchMaxMin and finds a quick derivative
	static eqnNode* derivative(eqnNode* expression, std::string var);

	/*
	 * eqnNode* collapse(eqnNode* input)
	 *
	 * Attempts to forcefully simplify an equation by combining all numbers
	 *	which are joined directly by operators
	 */
	static eqnNode* collapse(eqnNode* input);

	/*
	 * std::vector<eqnNode*> getCand(eqnNode* input);
	 *
	 * recursively parses the tree, generating all possible candidates
	 * 
	 */
	static std::vector<eqnNode*> getCand(eqnNode* input);
};
#endif
