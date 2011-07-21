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

#ifndef NN_CASSMACH_H
#define NN_CASSMACH_H

#include <vector>
#include "parsePart.h"

/*
 * class cassetteMachine
 *
 * Could be considered a counter-part to the altParse. Calls a list of 
 *	parseParts in sequence rather than parallel. Does not however return a
 * 	succ list in the usual format. It is left to the caller to decide
 *	how each parts' successes should be combined into a succ list
 */
class cassetteMachine
{
	protected:
	// the sequence of parseParts which will be run through
	std::vector<parsePart*> partlist;

	// a stack of individual parsePart successes, paired with an 
	//	integer index. This indicates which success was last considered
	//	when proceeding deeper into partlist
	std::vector<std::pair<int, std::vector<std::pair<int,eqnNode*> > > > cassette;

	// the usual parse cache, which will be passed to all subsequent
	//	parseParts
	std::map< std::pair<int,int>, std::vector<std::pair<int, eqnNode*> > > *fails;

	/*
	 * int goodCap()
	 * 
	 * Decides, by comparing the stack depth to the number of parseParts,
	 * whether or not to increase the cap.
	 */
	int goodCap() const;

	/*
	 * std::vector<std::pair <int, eqnNode*> > copySucc(const std::vector<std::pair <int, eqnNode*> > &list)
	 *
	 * Copies a succ list, same implementation as in parsePart
	 */
	std::vector<std::pair <int, eqnNode*> > copySucc(const std::vector<std::pair <int, eqnNode*> > &list) const;

	/*
	 * void collectSuccess()
	 *
	 * Iterates over the stack and collects the "current" eqnNode* from 
	 *	each parsePart, only in the case that a successful parse has 
	 *	been made by each parsePart in sequence.
	 */
	void collectSuccess(); 

	/*
	 * void popAndFree()
	 *
	 * frees all memory contained in the whichever succ list is at the 
	 * 	top of the cassette(stack), then pops it.  If this data is 
	 *	needed, it must be copied prior to freeing the parse part 
	 *	containing it.
	 */
	void popAndFree();

	/*
	 * bool endOfSucc()
	 *
	 * Checks the list off successes at the top of the stack, if the index 
	 *	here is greater than the size of the succ list here, 
	 *	endOfSucc() returns true.
	 */
	bool endOfSucc() const;

	/*
	 * int currentOffset()
	 *
	 * Finds the offset at the current index of the succ list at the top 
	 *	of the stack and returns the "offset" found there.
	 */
	int currentOffset () const;

	/*
	 * std::pair<int,std::vector<std::pair<int,eqnNode*> > > makeCMP(parsePart* input)
	 *
	 * Makes a copy of the succ list of the supplied parsePart and 
	 * 	combines it with the integer 0 in a std::pair. This integer 
	 *	acts as the index of the succ list.
	 */
	std::pair<int,std::vector<std::pair<int,eqnNode*> > > makeCMP(parsePart* input) const;
	
	public:
	// The list of successes, in a different form. The int represents the
	//	offset as usual, the eqnNode*'s however are left in pieces,
	//	the caller of the cassetteMachine decides how they will be 
	//	combined to form a proper succ list.
	std::vector<std::pair<int,std::vector<eqnNode*> > > pieces;

	/*
	 * void setMap( std::map< std::pair<int,int>, std::vector<std::pair<int, eqnNode*> > > *f)
	 *
	 * Assigns the parse cache to the supplied pointer.
	 */
	void setMap( std::map< std::pair<int,int>, std::vector<std::pair<int, eqnNode*> > > *f) { fails = f; }

	/*
	 * void add(parsePart* input)
	 *
	 * The supplied parsePart* is added to the partlist
	 */
	void add(parsePart* input);

	/*
	 * void loadString(int offset, const std::string& data, int cap)
	 * 
	 * This function initiates the parse. The offset, data, and cap are
	 * 	same values which will be supplied to each element of the 
	 *	partlist, modified as needed as the partlist is traversed.
	 */
	void loadString(int offset, const std::string& data, int cap);

	~cassetteMachine();
};


#endif
