/*
Copyright (c) 2013, Gil Brechbuhler
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of the Gil Brechbuhler nor the
  names of its contributors may be used to endorse or promote products
  derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND ANY
EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE REGENTS AND CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "juliaset.hpp"
#include <cmath>

JuliaSet::JuliaSet()
{
	move_x = 0;
	move_y = 0;
	zoom = 1;
	c = std::complex<double>(-0.7, 0.27015);
	max_iterations = 60;
}

void JuliaSet::increaseZoom(float frameTime)
{
	zoom *= pow(1.001, frameTime);
}

void JuliaSet::decreaseZoom(float frameTime)
{
	zoom /= pow(1.001, frameTime);
}

void JuliaSet::goRight(float frameTime)
{
	move_x += 0.0003 * frameTime / zoom;
}

void JuliaSet::goDown(float frameTime)
{
	move_y += 0.0003 * frameTime / zoom;
}

void JuliaSet::goLeft(float frameTime)
{
	move_x -= 0.0003 * frameTime / zoom;
}

void JuliaSet::goUp(float frameTime)
{
	move_y -= 0.0003 * frameTime / zoom;
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
