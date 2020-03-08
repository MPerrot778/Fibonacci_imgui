#pragma once

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <vector>

class fibonacci
{
public:
	fibonacci(std::vector<double> _buffer);
	~fibonacci();

	std::vector<double> createFib(double _pyramdidScale, double _nbrSpires);

	double lastValue(std::vector<double> buf);

	double getPyramidScale();
	double getNbrSpires();
	std::vector<double> getFibBuffer();

private:
	std::vector<double> computeFib(static std::vector<double> buffer);

	double pyramidScale;
	double nbrSpires;
	std::vector<double> fibBuffer;

};







#endif // !FIBONACCI_H
