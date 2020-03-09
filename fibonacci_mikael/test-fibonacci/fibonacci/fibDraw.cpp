#include "fibDraw.h"
#include "imgui.h"
#include <vector>

fibDraw::fibDraw(ImDrawList* _list)
{
	fibDrawList = _list;
}

fibDraw::~fibDraw()
{
}

void fibDraw::drawFibSpiral(double nbrSpirals, std::vector<double> fibBuffer, ImVec2 initPos, float scalling)
{
	float pi = 3.14159; // approx pi
	float temp_x;
	float temp_y;
	float spiral_size;
	float radius;

	ImVec2 center;
	ImVec2 spiral_start = initPos;
	ImVec2 spiral_end;
	ImVec2 c1;
	ImVec2 c2;

	ImDrawList* list = getFibList();
	auto col = IM_COL32(255, 0, 0, 255);

	for (int n = 1; n <= nbrSpirals; n++) {
		spiral_size = scalling * fibBuffer[n];
		switch (n%4)
		{
		case 0:

			// Find spiral corner
			temp_x = (double)spiral_start.x - spiral_size;
			temp_y = (double)spiral_start.y + spiral_size;
			spiral_end = ImVec2((float)temp_x, (float)temp_y);
			// Find center value between spiral_start and spiral_end
			temp_x = (double)spiral_start.x - spiral_size * 0.5;
			temp_y = (double)spiral_start.y + spiral_size * 0.5;
			center = ImVec2((float)temp_x, (float)temp_y);

			// Find spiral radius
			radius = sqrt(pow(((double)center.x - (double)spiral_start.x), 2) + pow(((double)center.x - (double)spiral_start.x), 2));

			// Find two more points on spiral arc (to have pi/3 and 2pi/3 rad between spiral_start point and c1/c2)
			temp_x = (double)center.x + radius * cos(7 * pi / 12);
			temp_y = (double)center.y - radius * sin(7 * pi / 12);
			c1 = ImVec2(temp_x, temp_y);
			temp_x = (double)center.x + radius * cos(11 * pi / 12);
			temp_y = (double)center.y - radius * sin(11 * pi / 12);
			c2 = ImVec2(temp_x, temp_y);

			// Approximate spiral with Bezier spline
			list->AddBezierCurve(spiral_start, c1, c2, spiral_end, col, 0.5f);

			// For next spiral
			spiral_start = spiral_end;
			break;

		case 1:
			// Find spiral corner
			temp_x = (double)spiral_start.x + spiral_size;
			temp_y = (double)spiral_start.y + spiral_size;
			spiral_end = ImVec2((float)temp_x,(float)temp_y);

			// Find center value between spiral_start and spiral_end
			temp_x = (double)spiral_start.x + spiral_size*0.5;
			temp_y = (double)spiral_start.y + spiral_size*0.5;
			center = ImVec2((float)temp_x, (float)temp_y);

			// Find spiral radius
			radius = sqrt(pow(((double)center.x - (double)spiral_start.x), 2) + pow(((double)center.x - (double)spiral_start.x), 2));

			// Find two more points on spiral arc (to have pi/3 and 2pi/3 rad between spiral_start point and c1/c2)
			temp_x = (double)center.x + radius*cos(13*pi/12);
			temp_y = (double)center.y - radius*sin(13*pi/12);
			c1 = ImVec2(temp_x, temp_y);
			temp_x = (double)center.x + radius*cos(17*pi/12);
			temp_y = (double)center.y - radius*sin(17*pi/12);
			c2 = ImVec2(temp_x, temp_y);

			// Approximate spiral with Bezier spline
			list->AddBezierCurve(spiral_start, c1, c2, spiral_end, col, 0.5f);

			// For next spiral
			spiral_start = spiral_end;
			break;

		case 2:

			// Find spiral corner
			temp_x = (double)spiral_start.x + spiral_size;
			temp_y = (double)spiral_start.y - spiral_size;
			spiral_end = ImVec2((float)temp_x, (float)temp_y);
			// Find center value between spiral_start and spiral_end
			temp_x = (double)spiral_start.x + spiral_size * 0.5;
			temp_y = (double)spiral_start.y - spiral_size * 0.5;
			center = ImVec2((float)temp_x, (float)temp_y);

			// Find spiral radius
			radius = sqrt(pow(((double)center.x - (double)spiral_start.x), 2) + pow(((double)center.x - (double)spiral_start.x), 2));

			// Find two more points on spiral arc (to have pi/3 and 2pi/3 rad between spiral_start point and c1/c2)
			temp_x = (double)center.x + radius * cos(19 * pi / 12);
			temp_y = (double)center.y - radius * sin(19 * pi / 12);
			c1 = ImVec2(temp_x, temp_y);
			temp_x = (double)center.x + radius * cos(23*pi / 12);
			temp_y = (double)center.y - radius * sin(23*pi / 12);
			c2 = ImVec2(temp_x, temp_y);

			// Approximate spiral with Bezier spline
			list->AddBezierCurve(spiral_start, c1, c2, spiral_end, col, 0.5f);

			// For next spiral
			spiral_start = spiral_end;
			break;

		case 3:

			// Find spiral corner
			temp_x = (double)spiral_start.x - spiral_size;
			temp_y = (double)spiral_start.y - spiral_size;
			spiral_end = ImVec2((float)temp_x, (float)temp_y);
			// Find center value between spiral_start and spiral_end
			temp_x = (double)spiral_start.x - spiral_size * 0.5;
			temp_y = (double)spiral_start.y - spiral_size * 0.5;
			center = ImVec2((float)temp_x, (float)temp_y);

			// Find spiral radius
			radius = sqrt(pow(((double)center.x - (double)spiral_start.x), 2) + pow(((double)center.x - (double)spiral_start.x), 2));

			// Find two more points on spiral arc (to have pi/3 and 2pi/3 rad between spiral_start point and c1/c2)
			temp_x = (double)center.x + radius * cos(pi / 12);
			temp_y = (double)center.y - radius * sin(pi / 12);
			c1 = ImVec2(temp_x, temp_y);
			temp_x = (double)center.x + radius * cos(5*pi / 12);
			temp_y = (double)center.y - radius * sin(5*pi / 12);
			c2 = ImVec2(temp_x, temp_y);

			// Approximate spiral with Bezier spline
			list->AddBezierCurve(spiral_start, c1, c2, spiral_end, col, 0.5f);

			// For next spiral
			spiral_start = spiral_end;
			break;

		default:
			break;
		}
	}
}

void fibDraw::drawfibSquare(double nbrSpirals, std::vector<double> fibBuffer, ImVec2 initPos, float scalling)
{

	float temp_x;
	float temp_y;
	float spiral_size;

	ImVec2 corner1 = initPos;
	ImVec2 corner2;
	ImVec2 corner3;
	ImVec2 corner4;

	ImDrawList* list = getFibList();
	auto col = IM_COL32(0, 0, 255, 255);

	for (int n = 1; n <= nbrSpirals; n++) {
		spiral_size = scalling * fibBuffer[n];
		switch (n%4)
		{

		case 0:
			temp_x = (double)corner1.x - spiral_size;
			temp_y = (double)corner1.y;
			corner2 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x - spiral_size;
			temp_y = (double)corner1.y + spiral_size;
			corner3 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x;
			temp_y = (double)corner1.y + spiral_size;
			corner4 = ImVec2(temp_x, temp_y);

			list->AddLine(corner1, corner2, col);
			list->AddLine(corner2, corner3, col);
			list->AddLine(corner3, corner4, col);
			list->AddLine(corner4, corner1, col);
			corner1 = corner3;
			break;

		case 1:

			temp_x = (double)corner1.x + spiral_size;
			temp_y = (double)corner1.y;
			corner2 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x + spiral_size;
			temp_y = (double)corner1.y + spiral_size;
			corner3 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x;
			temp_y = (double)corner1.y + spiral_size;
			corner4 = ImVec2(temp_x, temp_y);

			list->AddLine(corner1,corner2, col);
			list->AddLine(corner2, corner3, col);
			list->AddLine(corner3, corner4, col);
			list->AddLine(corner4, corner1, col);
			corner1 = corner3;
			break;

		case 2:

			temp_x = (double)corner1.x + spiral_size;
			temp_y = (double)corner1.y;
			corner2 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x + spiral_size;
			temp_y = (double)corner1.y - spiral_size;
			corner3 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x;
			temp_y = (double)corner1.y - spiral_size;
			corner4 = ImVec2(temp_x, temp_y);

			list->AddLine(corner1, corner2, col);
			list->AddLine(corner2, corner3, col);
			list->AddLine(corner3, corner4, col);
			list->AddLine(corner4, corner1, col);
			corner1 = corner3;
			break;

		case 3:

			temp_x = (double)corner1.x - spiral_size;
			temp_y = (double)corner1.y;
			corner2 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x - spiral_size;
			temp_y = (double)corner1.y - spiral_size;
			corner3 = ImVec2(temp_x, temp_y);
			temp_x = (double)corner1.x;
			temp_y = (double)corner1.y - spiral_size;
			corner4 = ImVec2(temp_x, temp_y);

			list->AddLine(corner1, corner2, col);
			list->AddLine(corner2, corner3, col);
			list->AddLine(corner3, corner4, col);
			list->AddLine(corner4, corner1, col);
			corner1 = corner3;
			break;

		default:
			break;
		}

	}


}

ImDrawList* fibDraw::getFibList()
{
	return fibDrawList;
}
