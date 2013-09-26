#ifndef JULIASET_HPP
#define JULIASET_HPP

#include <complex>

class JuliaSet
{
public:
	JuliaSet();
	void increaseZoom();
	void decreaseZoom();
	void goRight();
	void goDown();
	void goLeft();
	void goUp();
	void moreIterations();
	void lessIterations();
	double getMoveX();
	double getMoveY();
	double getZoom();
	std::complex<double> getC();
	int getMaxIterations();

private:
	double move_x;
	double move_y;
	double zoom;
	std::complex<double> c;
	int max_iterations;
};

#endif // JULIASET_HPP
