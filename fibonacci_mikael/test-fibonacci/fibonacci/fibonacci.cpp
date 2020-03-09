#include "fibonacci.h"
#include "imgui.h"
#include <math.h>

fibonacci::fibonacci(std::vector<double> _buffer)
{
	pyramidScale = 0;
	nbrSpirals = 0;
	fibBuffer = _buffer;
}

fibonacci::~fibonacci()
{
}

double fibonacci::getPyramidScale()
{
	return pyramidScale;
}

double fibonacci::getNbrSpirals()
{
	return nbrSpirals;
}

std::vector<double> fibonacci::getFibBuffer()
{
	return fibBuffer;
}

// Recursive function to create Fibonacci pyramid from scale value
std::vector<double> fibonacci::createFib(double _pyramdidScale, double _nbrSpirals)
{
	pyramidScale = _pyramdidScale;
	if (_nbrSpirals == 0) {
		nbrSpirals = pyramidScale;
	}
	else {
		nbrSpirals = _nbrSpirals;
	}
	fibBuffer = getFibBuffer();
	fibBuffer.resize(pyramidScale+1);

	fibBuffer = computeFib(fibBuffer);
	
	return fibBuffer;
}

// List all Fibonacci coefficients once pyramid is created
void fibonacci::listAll()
{
	std::vector<double> buf = getFibBuffer();
	double fibScale = getPyramidScale();

	for (int i = 0; i <= fibScale; i++) {
		ImGui::Text("F[%d] = %d", i, (int)buf[i]);
	}

}

// List only displayed coefficients
void fibonacci::listOnlyShowed()
{
	std::vector<double> buf = getFibBuffer();
	double fibScale = getNbrSpirals();

	for (int i = 0; i <= fibScale; i++) {
		ImGui::Text("F[%d] = %d", i, (int)buf[i]);
	}
}

// Get the value at the botom of the pyramid
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
