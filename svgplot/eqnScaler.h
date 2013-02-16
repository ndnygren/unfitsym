
#ifndef NN_EQNSCALER_H
#define NN_EQNSCALER_H

#include "configLoader.h"

class eqnScaler
{
	public:
	int px_width;
	int px_height;
	int eqn_x_min;
	int eqn_y_min;
	int eqn_x_max;
	int eqn_y_max;
	int border;

	int x(int input) const
	{
		return px_width * (input - eqn_x_min) / (eqn_x_max - eqn_x_min) + border;
	}

	int y(int input) const
	{
		return (border + px_height) - (px_height * (input - eqn_y_min) / (eqn_y_max - eqn_y_min));
	}

	void loadConfig(const configLoader& input)
	{
		border = configLoader::toInt(input["border"]);
		px_width = configLoader::toInt(input["px_width"]);
		px_height = configLoader::toInt(input["px_height"]);
		eqn_x_min = configLoader::toInt(input["eqn_x_min"]);
		eqn_y_min = configLoader::toInt(input["eqn_y_min"]);
		eqn_x_max = configLoader::toInt(input["eqn_x_max"]);
		eqn_y_max = configLoader::toInt(input["eqn_y_max"]);
	}

	int top() const { return y(eqn_y_min); }
	int bot() const { return y(eqn_y_max); }
	int left() const { return x(eqn_x_min); }
	int right() const { return x(eqn_x_max); }
};

#endif

