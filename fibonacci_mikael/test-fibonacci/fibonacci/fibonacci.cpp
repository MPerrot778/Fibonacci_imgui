#include "fibonacci.h"
#include <math.h>

fibonacci::fibonacci(std::vector<double> _buffer)
{
	pyramidScale = 0;
	nbrSpires = 0;
	fibBuffer = _buffer;
}

fibonacci::~fibonacci()
{
}

double fibonacci::getPyramidScale()
{
	return pyramidScale;
}

double fibonacci::getNbrSpires()
{
	return nbrSpires;
}

std::vector<double> fibonacci::getFibBuffer()
{
	return fibBuffer;
}

std::vector<double> fibonacci::createFib(double _pyramdidScale, double _nbrSpires)
{
	pyramidScale = _pyramdidScale;
	nbrSpires = _nbrSpires;
	fibBuffer = getFibBuffer();
	fibBuffer.resize(pyramidScale+1);

	fibBuffer = computeFib(fibBuffer);
	
	return fibBuffer;
}

double fibonacci::lastValue(std::vector<double> buf)
{
	double index = getPyramidScale();
	return buf[index];
}


std::vector<double> fibonacci::computeFib(static std::vector<double> buffer)
{
	static int n = 0;
	static float phi = (1 + sqrt(5)) / 2;
	static float phi_prime = -1 / phi;
	double temp = 0;

	if (n == getPyramidScale()) {

		temp = (pow(phi,n) - pow(phi_prime,n)) / sqrt(5);;
		buffer[n] = temp;
	}
	else
	{	
		n++;
		buffer = computeFib(buffer);
		n--;
		temp = (pow(phi,n) - pow(phi_prime,n)) / sqrt(5);
		buffer[n] = temp;
	}
	return buffer;
}
