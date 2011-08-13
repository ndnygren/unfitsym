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
#include "../../parse/nodes/intBNode.h"
#include "../../parse/nodes/lnNode.h"
#include "../../parse/nodes/sineNode.h"
#include "../../parse/nodes/cosineNode.h"
#include "../../parse/nodes/idxNode.h"
#include "../../parse/nodes/nodeTypes.h"

/**
 * @class alterExpression
 *
 * @brief Static functions, given any expression, a set of different but 
 * equivalent expressions are generated with a call to getCand()
 *
 * @details Specialized depending on the root node of the supplied expression.
 *
 * Recursive calls are made to the subtrees, manipulating the expression 
 *	independent of the rest of the tree
 *
 * All memory allocated is returned in the vector<eqnNode*> or is deallocated.
 * which ever function calls getCand() is responsible for freeing the 
 * vector's memory
 */


class alterExpression
{
	protected:

	/**
	 * @brief manipulates expressions with a root node of type sumNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> sumCand(sumNode* input);

	/**
	 * @brief manipulates expressions with a root node of type subNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> subCand(subNode* input);

	/**
	 * @brief manipulates expressions with a root node of type prodNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> prodCand(prodNode* input);

	/**
	 * @brief manipulates expressions with a root node of type fracNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> fracCand(fracNode* input);

	/**
	 * @brief manipulates expressions with a root node of type intNode (indefinte integrals)
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> intCand(intNode* input);

	/**
	 * @brief manipulates expressions with a root node of type intBNode (definite integrals)
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> intBCand(intBNode* input);

	/**
	 * @brief manipulates expressions with a root node of type lnNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> lnCand(lnNode* input);

	/**
	 * @brief manipulates expressions with a root node of type cosineNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> cosineCand(cosineNode* input);

	/**
	 * @brief manipulates expressions with a root node of type sineNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> sineCand(sineNode* input);

	/**
	 * @brief manipulates expressions with a root node of type derivNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> derivCand(derivNode* input);

	/**
	 * @brief manipulates expressions with a root node of type negNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> negCand(negNode* input);

	/**
	 * @brief manipulates expressions with a root node of type hatNode
	 * @param input the expression to be manipulated
	 * @returns a list of equivalent expressions, manipulated slightly
	 */
	static std::vector<eqnNode*> hatCand(hatNode* input);

	/**
	 * @brief attempts to integrate by substitution
	 * @param input the expression to be integrated
	 * @param var the variable of integration
	 * @returns the result of integration, if successful, otherwise null
	 */
	static eqnNode* substitute(prodNode* input, std::string var);

	// eqnNode* attemptStrip(intNode* input);
	/**
	 * @brief solves the integral in such a way that the result contains to 
	 *	remaining integrals, method common to definite and indefinite integrals
	 *	
	 * @param input the integral expression to evaluate
	 * @returns a evaluated expression, or null if evaluation fails
	 */
	static eqnNode* attemptStrip(intNode* input);

	/**
	 * @brief locates the largest x in use in the form C_{x}
	 * @param input The expression to be searched
	 * @returns the maximum index, x
	 */
	static int maxIndex(eqnNode* input);

	/**
	 * @brief replaces newly created C_{replace} nodes with proper unique indices
	 * @param input The expression to be searched
	 * @param newindex the new index for all 'replace' nodes
	 */
	static void setIndex(eqnNode* input, int newindex);

	// vector<eqnNode*> getAssocVector(binOpNode* input)
	/**
	 * @brief Breaks the expression into a list of expressions representing the general associative form.
	 * @param input the expression to be broken
	 * @returns the statement in a vector form
	 */
	static std::vector<eqnNode*> getAssocVector(binOpNode* input);

	/**
	 * @brief combines a list of expressions into a product of expressions
	 * @param list the list of expressions to be combined
	 * @returns the product of all expressions in the list
	 */
	static eqnNode* buildProduct(std::vector<eqnNode*>& list);

	/**
	 * @brief combines a list of expressions into a sum of expressions
	 * @param list the list of expressions to be combined
	 * @returns the sum of all expressions in the list
	 */
	static eqnNode* buildSum(std::vector<eqnNode*>& list);

	/**
	 * @brief sorted/grouped assoc vector construction
	 * @details groups expressions by their "bases", each with a list of their "arguments"
	 * @param brklist The output list of expression groups
	 * @param base the group to the argument add to
	 * @param arg the argument to add to the group
	 */
	static void pushToBrk(std::vector<std::pair<eqnNode*, std::vector<eqnNode*> > >& brklist, eqnNode* base, eqnNode* arg);


	// void negList(vector<eqnNode*>& list)
	/**
	 * @brief multiplies every list element by -1
	 *
	 * @param list the list of expressions to be multiplyied by negative one
	 *
	 */
	static void negList(std::vector<eqnNode*>& list);

	// void unSub(vector<eqnNode*>& input)
	/**
	 * @brief attempts to express all differences as sums, -1*
	 * @param input the list of expressions to be broken
	 */
	static void unSub(std::vector<eqnNode*>& input);


	// void invertList(vector<eqnNode*>& list)
	/**
	 * @brief takes every exponent in the list to exp(-1)
	 * @param list the list of expressions to be inverted
	 */
	static void invertList(std::vector<eqnNode*>& list);

	//void unFrac(vector<eqnNode*> input)
	/**
	 * @brief attempts to express all fractions as products, using exp(-1)
	 * @param input the list of expressions to be broken
	 */
	static void unFrac(std::vector<eqnNode*>& input);
	

	// eqnNode* sumSimplify(sumNode* input)
	/**
	 * @brief rapid simplification of sums, by general associativity and comutivity
	 * @details The sum is broken into terms, sorted grouped, collapsed and merged into another hopefully smaller expression, in a single step.
	 * @param input the expression to be simplified.
	 *
	 * @returns the simplified expression
	 *
	 */
	static eqnNode* sumSimplify(sumNode* input);

	// eqnNode* prodSimplify(sumNode* input)
	/**
	 * @brief rapid simplification of products, by general associativity and comutivity
	 * @details The product is broken into terms, sorted grouped, collapsed and merged into another hopefully smaller expression, in a single step.
	 * @param input the expression to be simplified.
	 *
	 * @returns the simplified expression
	 */
	static eqnNode* prodSimplify(prodNode* input);

	/**
	 * @brief Compares 2 expressions to determine if they differ only by scalar multiplication
	 * @param actual the found expression
	 * @param expected the desired expression
	 * @returns the required scalar multiple, if possible, otherwise null
	 */
	static eqnNode* scalarCompare(eqnNode* actual, eqnNode* expected);

	public:
	/**
	 * @brief replaces newly created C_{replace} nodes with the next index
	 * @param input The expression to be searched
	 */
	static void replaceIndex(eqnNode* input)
	{
		setIndex(input,maxIndex(input)+1);
	}

	/**
	 * @brief creates a vector copy, allocating new memory
	 * @param from the source vector
	 * @param to the destination vector
	 */
	static void copyCand(const std::vector<eqnNode*>& from, std::vector<eqnNode*>& to); 

	/**
	 * @brief frees all memory in the vector
	 * @param list the list containing memeory to be freed
	 */
	static void freeCand(std::vector<eqnNode*>& list);

	/**
	 * @brief calls searchMaxMin and finds a quick derivative
	 * @param expression The expression to be differentiated
	 * @param var the variable of differentiation
	 * @returns a expression representing the derivative of the supplied expression.
	 */
	static eqnNode* derivative(eqnNode* expression, std::string var);

	// std::vector<eqnNode*> getCand(eqnNode* input);
	/**
	 * @brief recursively traverses the tree, generating equivalent candidate expressions by simple manipulations
	 * @param input the expression to be manipulated
	 * 
	 * @returns a list of expressions, all equivalent to the original input.
	 */
	static std::vector<eqnNode*> getCand(eqnNode* input);
};
#endif
