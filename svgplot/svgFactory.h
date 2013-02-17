

#ifndef NN_SVGFACTORY_H
#define NN_SVGFACTORY_H

#include "eqnScaler.h"
#include "../parse/parserFull.h"
#include <cmath>

class svgFactory
{
	eqnScaler scale;
	configLoader cfg;

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
	void loadConfig(const configLoader& input)
	{
		scale.loadConfig(input);
		cfg = input;
	}

	svgFactory(const configLoader& input)
	{
		loadConfig(input);
	}

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
			num = new numNode(i);
			temp = eqn->copy();
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

