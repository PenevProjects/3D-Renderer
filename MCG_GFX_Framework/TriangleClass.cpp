#include "TriangleClass.h"



TriangleClass::TriangleClass()
{
}


TriangleClass::~TriangleClass()
{
}

void TriangleClass::Line(glm::ivec2 _a, glm::ivec2 _b, glm::vec3 color) //utilizing Bresenham's algorithm
{
	int dx, dy; //delta x, delta y
	int stepx, stepy; //x step, y step

	dx = _b.x - _a.x; // change in x
	dy = _b.y - _a.y; // change in y

	if (dy < 0) // if change in y is less than 0, y0 > y1, meaning line goes up and right
	{
		dy = -dy; //need negative of m from y = mx + c, so dy = -dy
		stepy = -1; //step by going upwards instead of downwards
	}
	else
		stepy = 1; // step by going down
	if (dx < 0) // x0 > x1, meaning right to left
	{
		dx = -dx; //need negative of m
		stepx = -1; // step by going right to left
	}
	else
	{
		stepx = 1; // step by going left to right
	}


	if (dx > dy)
	{
		int fraction = (dy * 2) - dx; // see reference[1] for proof of initial fraction value
		while (_a.x != _b.x) // while y0 is different than y1
		{
			MCG::DrawPixel(glm::vec2(_a.x, _a.y), color);
			_a.x += stepx; //increment x
			if (fraction >= 0) //if fraction is positive, we have reached the y change
			{
				_a.y += stepy; //increment y
				fraction -= dx; //subtract dx from fraction (from dx > dy)
			}
			fraction += dy; //add dy to fraction to keep track when we need to increment y

		}
	}
	else //when dy > dx
	{
		/* vice versa from the if statement*/
		int fraction = (dx * 2) - dy;
		while (_a.y != _b.y)
		{

			MCG::DrawPixel(glm::vec2(_a.x, _a.y), color);
			_a.y += stepy;
			if (fraction >= 0)
			{
				_a.x += stepx;
				fraction -= dy;
			}
			fraction += dx;
		}
	}
}
void TriangleClass::DrawTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color) 
{
	Line({ v1.x, v1.y }, { v2.x, v2.y }, color);
	Line({ v2.x, v2.y }, { v3.x, v3.y }, color);
	Line({ v3.x, v3.y }, { v1.x, v1.y }, color);
}
void TriangleClass::fillBottomFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color) 
{
	/* will need the change in X for both lines that connect in point v1,
	m = dx/dy which is 1/m, we need change in X per step in Y
	this algorithm utilizes top-left rasterization rule*/
	float slope1 = (v2.x - v1.x) / (v2.y - v1.y); // left line slope
	float slope2 = (v3.x - v1.x) / (v3.y - v1.y); // right line slope

	int startY = (int)ceil(v1.y - 0.5f); //scanline's Y of first line( subtract 0.5f because we are calculating based on pixel centers, implementing top part of top-left rule)
	int endY = (int)ceil(v3.y - 0.5f); //scanline's Y after last line drawn( subtract 0.5f because we are calculating based on pixel centers, implementing top part of top-left rule)

	for (int currentY = startY; currentY < endY; currentY++)
	{
		float currentX0 = slope1 * (currentY + 0.5f - v2.y) + v2.x; // calculate current X by: Divide the distance from starting point to the currentY, by deltaY, multiply that by deltaX then add v1.x
		float currentX1 = slope2 * (currentY + 0.5f - v3.y) + v3.x; // calculate current X by: Divide: (the distance from starting point to the currentY), by deltaY, multiply that by deltaX then add v1.x

		int xStart = (int)ceil(currentX0 - 0.5f); //scanline's starting X, implementing left part of top-left rule
		int xEnd = (int)ceil(currentX1 - 0.5f); //scanline's last X implementing left part of top-left rule
		Line({ xStart, currentY }, { xEnd, currentY }, color); // draws line between current xStart and xEnd at the current Y value
	}
}
void TriangleClass::fillTopFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color)
{
	/* will need the change in X for both lines that connect in point v3,
	m = dx/dy which is 1/m, we need change in X per step in Y
	this algorithm utilizes top-left rasterization rule*/
	float slope1 = (v3.x - v1.x) / (v3.y - v1.y); // left line slope
	float slope2 = (v3.x - v2.x) / (v3.y - v2.y); // right line slope

	int startY = (int)ceil(v1.y - 0.5f); //scanline's Y of first line( subtract 0.5f because we are calculating based on pixel centers, implementing top part of top-left rule)
	int endY = (int)ceil(v3.y - 0.5f); //scanline's Y after last line drawn

	for (int currentY = startY; currentY < endY; currentY++)
	{
		float currentX0 = slope1 * (currentY + 0.5f - v1.y) + v1.x; // calculate current X by: Divide the distance from starting point to the currentY, by deltaY, multiply that by deltaX then add v1.x
		float currentX1 = slope2 * (currentY + 0.5f - v2.y) + v2.x; // calculate current X by: Divide: (the distance from starting point to the currentY), by deltaY, multiply that by deltaX then add v1.x

		int xStart = (int)ceil(currentX0 - 0.5f); //scanline's starting X, implementing left part of top-left rule
		int xEnd = (int)ceil(currentX1 - 0.5f); //scanline's last X
		Line({ xStart, currentY }, { xEnd, currentY }, color); // draws line between current xStart and xEnd at the current Y value
	}
}
void TriangleClass::FillTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color)
{
	//sort
	if (v1.y > v2.y) std::swap(v1, v2);
	if (v1.y > v3.y) std::swap(v1, v3);
	if (v2.y > v3.y) std::swap(v2, v3);


	if (v2.y == v3.y) // flat bottom
	{
		if (v3.x < v2.x) std::swap(v2, v3); // sorting bottom vertices by x
		fillBottomFlatTriangle(v1, v2, v3, color);
	}
	else if (v1.y == v2.y) // flat top
	{
		if (v2.x < v1.x) std::swap(v1, v2); // sorting top vertices by x
		fillTopFlatTriangle(v1, v2, v3, color);
	}
	else
	{
		//find splitting vertex
		float ratio = (v2.y - v1.y) / (v3.y - v1.y); //ratio between 2 sides
		glm::vec2 vSplit = v1 + (v3 - v1) * ratio;

		if (v2.x < vSplit.x) // major right triangle
		{
			fillBottomFlatTriangle(v1, v2, vSplit, color);
			fillTopFlatTriangle(v2, vSplit, v3, color);
		}
		else // major left triangle
		{
			fillBottomFlatTriangle(v1, vSplit, v2, color);
			fillTopFlatTriangle(vSplit, v2, v3, color);
		}
	}
}