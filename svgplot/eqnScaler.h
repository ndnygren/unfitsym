
#ifndef NN_EQNSCALER_H
#define NN_EQNSCALER_H

#include "configLoader.h"

class eqnScaler
{
	int px_width;
	int px_height;
	int eqn_x_min;
	int eqn_y_min;
	int eqn_x_max;
	int eqn_y_max;
	int border;

	public:
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
		border = input["border"];
		px_width = input["px_width"];
		px_height = input["px_height"];
		eqn_x_min = input["eqn_x_min"];
		eqn_y_min = input["eqn_y_min"];
		eqn_x_max = input["eqn_x_max"];
		eqn_y_max = input["eqn_y_max"];
	}
};

#endif

