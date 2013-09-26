#ifndef COLORTOOLS_HPP
#define COLORTOOLS_HPP

#include <SFML/Graphics.hpp>

class ColorTools
{
public:
	ColorTools();
	virtual ~ColorTools();

	static sf::Color hsvToRgb(int h, double s, double v);
};

#endif // COLORTOOLS_HPP
