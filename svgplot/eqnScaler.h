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


#ifndef NN_EQNSCALER_H
#define NN_EQNSCALER_H

#include "configLoader.h"


/**
 * @brief Based on image size, and graph size, maps from graph coordinates to image coordinates
 */
class eqnScaler
{
	public:
	/** @brief The width of the image */
	int px_width;
	/** @brief The height of the image */
	int px_height;
	/** @brief The low side of the x interval */
	double eqn_x_min;
	/** @brief The low side of the y interval */
	double eqn_y_min;
	/** @brief The high side of the x interval */
	double eqn_x_max;
	/** @brief The high side of the y interval */
	double eqn_y_max;
	/** @brief The thickness of the border, and other visual effects */
	int border;
	/** @brief The step size, for estimating the curve */
	double step;

	/**
	 * @brief Maps the x coordinate from graph to image
	 * @param input The variable in graph coordinates
	 * @return The variable in image coordinates
	 */
	int x(double input) const
	{
		return (int)(px_width * (input - eqn_x_min) / (eqn_x_max - eqn_x_min)) + border;
	}

	/**
	 * @brief Maps the y coordinate from graph to image
	 * @param input The variable in graph coordinates
	 * @return The variable in image coordinates
	 */
	int y(double input) const
	{
		return (int)((border + px_height) - (px_height * (input - eqn_y_min) / (eqn_y_max - eqn_y_min)));
	}

	/**
	 * @brief Performs string to number conversions and stores result for easy access
	 * @param input The result of the config file parse
	 */
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

	/** @brief The top of the image in image coordinates */
	int top() const { return y(eqn_y_min); }

	/** @brief The bottom of the image in image coordinates */
	int bot() const { return y(eqn_y_max); }

	/** @brief The left of the image in image coordinates */
	int left() const { return x(eqn_x_min); }

	/** @brief The right of the image in image coordinates */
	int right() const { return x(eqn_x_max); }
};

#endif

