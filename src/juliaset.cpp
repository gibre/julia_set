#include "juliaset.hpp"

JuliaSet::JuliaSet()
{
	move_x = 0;
	move_y = 0;
	zoom = 1;
	c = std::complex<double>(-0.7, 0.27015);
	max_iterations = 60;
}

void JuliaSet::increaseZoom()
{
	zoom *= 2;
}

void JuliaSet::decreaseZoom()
{
	zoom /= 2;
}

void JuliaSet::goRight()
{
	move_x += 0.9 / zoom;
}

void JuliaSet::goDown()
{
	move_y += 0.9 / zoom;
}

void JuliaSet::goLeft()
{
	move_x -= 0.9 / zoom;
}

void JuliaSet::goUp()
{
	move_y -= 0.9 / zoom;
}

void JuliaSet::moreIterations()
{
	max_iterations *= 2;
}

void JuliaSet::lessIterations()
{
	if (max_iterations > 2)
		max_iterations /= 2;
}

double JuliaSet::getMoveX()
{
	return this->move_x;
}

double JuliaSet::getMoveY()
{
	return this->move_y;
}

double JuliaSet::getZoom()
{
	return this->zoom;
}

std::complex<double> JuliaSet::getC()
{
	return this->c;
}

int JuliaSet::getMaxIterations()
{
	return this->max_iterations;
}
