#pragma once

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "imgui.h"
#include <vector>

class fibonacci
{
public:
	fibonacci(std::vector<double> _buffer);
	~fibonacci();

	std::vector<double> createFib(double _pyramdidScale, double _nbrSpirals=0);
	void listAll();
	void listOnlyShowed();
	double lastValue(std::vector<double> buf);

	double getPyramidScale();
	double getNbrSpirals();
	std::vector<double> getFibBuffer();

private:
	std::vector<double> computeFib(static std::vector<double> buffer);

	double pyramidScale;
	double nbrSpirals;
	std::vector<double> fibBuffer;

};







#endif // !FIBONACCI_H
