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
#include "sumAlt.h"
#include "subAlt.h"
#include "prodAlt.h"
#include "fracAlt.h"
#include "negAlt.h"
#include "hatAlt.h"
#include "derivAlt.h"
#include "intAlt.h"
#include "cosineAlt.h"
#include "sineAlt.h"
#include "lnAlt.h"


std::vector<eqnNode*> getCand(eqnNode* input);
void copyCand(const std::vector<eqnNode*>& from, std::vector<eqnNode*>& to); 
void freeCand(std::vector<eqnNode*>& list);

#endif
