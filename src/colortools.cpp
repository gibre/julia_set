#include "colortools.hpp"

sf::Color ColorTools::hsvToRgb(int h, double s, double v)
{
	sf::Color color;

	if (h > 360)
		h = 360;
	else if (h < 0)
		h = 0;
	if (s > 1)
		s = 1;
	else if (s < 0)
		s = 0;
	if (v > 1)
		v = 1;
	else if (v < 0)
		v = 0;

	int t_i = h/60;
	double f = ((double) h/60.0f) - t_i;
	double l = v * (1 - s);
	double  m = v * (1 - f * s);
	double n = v * (1 - (1 - f));

	switch (t_i) {
	case 0:
		color.r = (int) (v * 255);
		color.g = (int) (n * 255);
		color.b = (int) (l * 255);
		break;
	case 1:
		color.r = (int) (m * 255);
		color.g = (int) (v * 255);
		color.b = (int) (l * 255);
		break;
	case 2:
		color.r = (int) (l * 255);
		color.g = (int) (v * 255);
		color.b = (int) (n * 255);
		break;
	case 3:
		color.r = (int) (l * 255);
		color.g = (int) (m * 255);
		color.b = (int) (v * 255);
		break;
	case 4:
		color.r = (int) (n * 255);
		color.g = (int) (l * 255);
		color.b = (int) (v * 255);
		break;
	case 5:
		color.r = (int) (v * 255);
		color.g = (int) (l * 255);
		color.b = (int) (m * 255);
		break;
	}

	return color;
}
