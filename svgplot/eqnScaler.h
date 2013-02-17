
#ifndef NN_EQNSCALER_H
#define NN_EQNSCALER_H

#include "configLoader.h"

class eqnScaler
{
	public:
	int px_width;
	int px_height;
	double eqn_x_min;
	double eqn_y_min;
	double eqn_x_max;
	double eqn_y_max;
	int border;
	double step;

	int x(double input) const
	{
		return (int)(px_width * (input - eqn_x_min) / (eqn_x_max - eqn_x_min)) + border;
	}

	int y(double input) const
	{
		return (int)((border + px_height) - (px_height * (input - eqn_y_min) / (eqn_y_max - eqn_y_min)));
	}

	void loadConfig(const configLoader& input)
	{
		border = configLoader::toInt(input["border"]);
		px_width = configLoader::toInt(input["px_width"]);
		px_height = configLoader::toInt(input["px_height"]);
		eqn_x_min = configLoader::toDouble(input["eqn_x_min"]);
		eqn_y_min = configLoader::toDouble(input["eqn_y_min"]);
		eqn_x_max = configLoader::toDouble(input["eqn_x_max"]);
		eqn_y_max = configLoader::toDouble(input["eqn_y_max"]);
		step = configLoader::toDouble(input["step"]);
	}

	int top() const { return y(eqn_y_min); }
	int bot() const { return y(eqn_y_max); }
	int left() const { return x(eqn_x_min); }
	int right() const { return x(eqn_x_max); }
};

#endif

