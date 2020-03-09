#pragma once

#ifndef FIBDRAW_H
#define FIBDRAW_H

#include "imgui.h"
#include <vector>

class fibDraw
{
public:
	fibDraw(ImDrawList* _list);
	~fibDraw();
	
	void drawFibSpiral(double nbrSpirals, std::vector<double> fibBuffer, ImVec2 initPos,float scalling = 1);
	void drawfibSquare(double nbrSpirals, std::vector<double> fibBuffer, ImVec2 initPos,float scalling = 1);

	ImDrawList* getFibList();

private:
	ImDrawList* fibDrawList;
};







#endif // !FIBONACCI_H