

#ifndef NN_SVGFACTORY_H
#define NN_SVGFACTORY_H

#include "eqnScaler.h"

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
		if (scale.eqn_x_min <= 0 && scale.eqn_y_max >= 0)
		{
			return line(scale.x(0), scale.px_height + 3*scale.border/2, scale.x(0), scale.border/2);
		}
		else if (scale.eqn_x_min > 0)
		{
			return line(scale.border/2, scale.px_height + 3*scale.border/2, scale.border/2, scale.px_height + scale.border/2);
		}
		else
		{
			return line(scale.px_width + scale.border/2, scale.px_height + 3*scale.border/2, scale.px_width + scale.border/2, scale.px_height + scale.border/2);
		}

	}

	std::string h_axis() const
	{
		if (scale.eqn_y_min <= 0 && scale.eqn_y_max >= 0)
		{
			return line(scale.border/2,
				scale.y(0),
				scale.px_width + 3*scale.border/2,
				scale.y(0));
		}
		else if (scale.eqn_y_min > 0)
		{
			return line(scale.border/2,
				scale.border/2,
				scale.px_width + 3*scale.border/2,
				scale.border/2);
		}
		else
		{
			return line(scale.border/2,
				scale.px_height + 3*scale.border/2,
				scale.px_width + 3*scale.border/2,
				scale.px_height + 3*scale.border/2);
		}

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
		output << "</svg>\n";

		return output.str();
	}
};

#endif

