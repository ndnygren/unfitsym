/* svgplot - framework for symbolic computation
* Copyright (C) 2013 Nick Nygren
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


#ifndef NN_SVGFACTORY_H
#define NN_SVGFACTORY_H

#include "eqnScaler.h"
#include "../parse/parserFull.h"
#include <cmath>


/**
 * @brief Based on a supplied config file, creates an svg image
 */
class svgFactory
{
	/** @brief Scaler and storage for parsed/converted config variables */
	eqnScaler scale;

	/** @brief The raw, parsed but unconverted config strings*/
	configLoader cfg;

	/**
	 * @brief Generates a svg-formatted line string from (x1,y1) to (x2,y2)
	 * @param x1 First x coordinate
	 * @param y1 First y coordinate
	 * @param x2 Second x coordinate
	 * @param y2 Second y coordinate
	 * @return The formatted string
	 */
	std::string line(int x1, int y1, int x2, int y2) const
	{
		std::stringstream ss;

		ss << "<line x1=\"" << x1;
		ss << "\" y1=\"" << y1;
		ss << "\" x2=\"" << x2;
		ss << "\" y2=\"" << y2; 
		ss << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\"" << " />\n";
		return ss.str();
	}

	/**
	 * @brief Locates the proper location for the vertical axis and generates an svg string to draw it
	 * @return The formatted string
	 */
	std::string v_axis() const
	{
		int xval;
		std::string output;
		int inc = scale.border/2;
		double i;

		if (scale.eqn_x_min <= 0 && scale.eqn_x_max >= 0)
			{ xval = scale.x(0); }
		else if (scale.eqn_x_min > 0)
			{ xval = inc; }
		else
			{ xval = scale.px_width + 3*inc; }

		output = line(xval, scale.px_height + scale.border, xval, scale.border);
		output += line(xval - inc/2, scale.border + inc/2, xval, scale.border);
		output += line(xval + inc/2, scale.border + inc/2, xval, scale.border);
		for (i = ceil(scale.eqn_y_min); i < scale.eqn_y_max; i++)
		{
			output += line(xval - inc/2, scale.y(i), xval, scale.y(i));
		}

		return output;
	}

	/**
	 * @brief Locates the proper location for the horizontal axis and generates an svg string to draw it
	 * @return The formatted string
	 */
	std::string h_axis() const
	{
		int yval;
		std::string output;
		int inc = scale.border/2;
		double i;

		if (scale.eqn_y_min <= 0 && scale.eqn_y_max >= 0)
			{ yval = scale.y(0); }
		else if (scale.eqn_y_min > 0)
			{ yval = scale.px_height + 3*inc; }
		else
			{ yval = inc; }
		output = line(scale.border, yval, scale.px_width + scale.border, yval);
		output += line(scale.px_width + scale.border - inc/2, yval - inc/2, scale.px_width + scale.border, yval);
		output += line(scale.px_width + scale.border - inc/2, yval + inc/2, scale.px_width + scale.border, yval);
		for (i = ceil(scale.eqn_x_min); i < scale.eqn_x_max; i++)
		{
			output += line(scale.x(i), yval+inc/2, scale.x(i), yval);
		}

		return output;
	}

	public:
	/**
	 * @brief Links the factory to a existing configLoader
	 * @param input The configLoader
	 */
	void loadConfig(const configLoader& input)
	{
		scale.loadConfig(input);
		cfg = input;
	}

	svgFactory(const configLoader& input)
	{
		loadConfig(input);
	}

	/**
	 * @brief Generates a svg path from a LaTeX formated function
	 * @param input The LaTeX formatted equation
	 * @return The svg path string
	 */
	std::string makeCurve(const std::string& input) const
	{
		std::stringstream ss;
		double i;
		eqnNode* eqn = parserFull::getExpr(input);
		eqnNode* temp;
		eqnNode* num;

		if (eqn == 0) 
		{
			std::cerr << "Error parsing " << input << "." << std::endl;
			return "";
		}

		ss << "<path d=\"";

		for (i = scale.eqn_x_min; i <= scale.eqn_x_max; i += scale.step)
		{
			// generating a 'number' node containing 'i' as its value
			num = new numNode(i);
			// initializing temp with the equation
			temp = eqn->copy();
			// substituting the value 'i' for every occurance of 'x' in the equation
			temp->replace("x", num);

			std::cerr << i << "\t->\t" << temp->nice_str() << "=" << temp->value() << std::endl;
			if (i == scale.eqn_x_min) { ss << "M "; }
			else { ss << "L "; }

			ss << scale.x(i) << " " << scale.y(temp->value()) << " ";
			delete num;
			delete temp;
		}

		ss << "\" fill=\"none\" stroke=\"red\" stroke-width=\"3\"/>\n";

		delete eqn;

		return ss.str(); 
	}

	/**
	 * @brief Generates the entire svg file
	 * @return The svg formatted string
	 */
	std::string toString() const
	{
		std::stringstream output;

		output << "<?xml version=\"1.1\"?>\n";
		output << "<svg xmlns=\"http://www.w3.org/2000/svg\"";
		output << " width=\"" << (2*scale.border + scale.px_width); 
		output << "\" height=\"" << (2*scale.border + scale.px_height); 
		output << "\" viewbox=\"0 0 ";
		output << (2*scale.border + scale.px_width) << " ";
		output << (2*scale.border + scale.px_height) << "\">\n";
		output << v_axis();
		output << h_axis();

		output << "<rect x=\"" << scale.left() << "\" y=\"" << scale.bot();
		output << "\" width=\"" << scale.right() - scale.left();
		output << "\" height=\"" << scale.top() - scale.bot();
		output << "\" style=\"stroke:rgb(0,0,0);stroke-width:1\"";
		output << " fill=\"none\"/>\n";

		output << makeCurve(cfg["eqn1"]);

		output << "</svg>\n";

		return output.str();
	}
};

#endif

