#include "Shape2D.h"




Shape2D::Shape2D(glm::vec3 _color) 
	: color(_color)
{
}


Shape2D::Shape2D(const Shape2D& _copy) 
	: PositionVec(_copy.getPositionVector()),
	color(_copy.getColor())
{
}
Shape2D::Shape2D(const Shape2D& _copy, glm::ivec3 _color) 
	: PositionVec(_copy.getPositionVector()),
	color(_color)
{
}

Shape2D::~Shape2D()
{
}

glm::vec3 Shape2D::getColor() const
{
	return color;
}
void Shape2D::setColor(glm::vec3 _color)
{
	color = _color;
}

void Shape2D::pushbackPosition(int x, int y)
{
	PositionVec.push_back(glm::vec2(x, y));
}
std::vector<glm::vec2> Shape2D::getPositionVector() const
{
	return PositionVec;
}
glm::vec2& Shape2D::getPositionAt(int i)
{
	return PositionVec.at(i);
}

void Shape2D::DrawSquareGradient(glm::vec3 _c1, glm::vec3 _c2, int _len)
{
	glm::vec3 result;
	for (int stepY = 10; stepY < _len; ++stepY)
	{
		for (int stepX = 10; stepX < _len; ++stepX)
		{
			result.x = (_c2.x - _c1.x) * stepX / _len + _c1.x;
			result.y = (_c2.y - _c1.y) * stepX / _len + _c1.y;
			result.z = (_c2.z - _c1.z) * stepX / _len + _c1.z;
			MCG::DrawPixel({ stepX, stepY }, result);
		}
	}
}
void Shape2D::DrawSquareFilled(glm::vec3 _color, int _len)
{
	for (int stepY = 10; stepY < _len; ++stepY)
	{
		for (int stepX = 10; stepX < _len; ++stepX)
		{
			MCG::DrawPixel({ stepX, stepY }, _color);
		}
	}
}
void Shape2D::DrawSquareOutline(glm::vec3 _color, glm::ivec2 topLeft, glm::ivec2 botRight)
{
	Line(topLeft, { topLeft.x, botRight.y }, _color);
	Line({ topLeft.x, botRight.y }, botRight, _color);
	Line(topLeft, { botRight.x, topLeft.y }, _color);
	Line({ botRight.x, topLeft.y }, botRight, _color);
}
void Shape2D::DrawCircleOutline(glm::vec2 _center, int r, glm::vec3 _color)
{
	int x = 0, y = r; //start from (0,1)
	int d = 3 - (2 * r); //decision parameter, check reference[7] for initial value proof
	//draw initial pixels for every octant (basically every 45 degrees)
	MCG::DrawPixel({ _center.x + x, _center.y + y }, _color);
	MCG::DrawPixel({ _center.x - x, _center.y + y }, _color);
	MCG::DrawPixel({ _center.x + x, _center.y - y }, _color);
	MCG::DrawPixel({ _center.x - x, _center.y - y }, _color);
	MCG::DrawPixel({ _center.x + y, _center.y + x }, _color);
	MCG::DrawPixel({ _center.x - y, _center.y + x }, _color);
	MCG::DrawPixel({ _center.x + y, _center.y - x }, _color);
	MCG::DrawPixel({ _center.x - y, _center.y - x }, _color);
	while (x <= y) //while x less or equal than y, meaning until we reach the 45degree coordinate after which x>y
	{
		++x; //increment x
		if (d < 0) //if decision parameter is less than 0, meaning the next pixel is east{x+1, y}
			d += (4 * x) + 6; //recalculate decision parameter with new X value(again [7] for proof)
		else //else decision parameter is >=0, meaning the next pixel is south-east{x+1, y-1}
		{
			d += 4 * (x - y) + 10; // [7]
			y--; //decrement x
		}
		//draw pixel for every octant
		MCG::DrawPixel({ _center.x + x, _center.y + y }, _color);
		MCG::DrawPixel({ _center.x - x, _center.y + y }, _color);
		MCG::DrawPixel({ _center.x + x, _center.y - y }, _color);
		MCG::DrawPixel({ _center.x - x, _center.y - y }, _color);
		MCG::DrawPixel({ _center.x + y, _center.y + x }, _color);
		MCG::DrawPixel({ _center.x - y, _center.y + x }, _color);
		MCG::DrawPixel({ _center.x + y, _center.y - x }, _color);
		MCG::DrawPixel({ _center.x - y, _center.y - x }, _color);
	}
}
void Shape2D::DrawCircleFilledBres(glm::vec2 _center, int r, glm::vec3 _color)
{
	int x = 0, y = r; //start from (0,1)
	int d = 3 - (2 * r); //decision parameter, check reference[7] for initial value proof
	//draw initial pixels for every octant (basically every 45 degrees)
	Line(_center, { _center.x + x, _center.y + y }, _color);
	Line(_center, { _center.x - x, _center.y + y }, _color);
	Line(_center, { _center.x + x, _center.y - y }, _color);
	Line(_center, { _center.x - x, _center.y - y }, _color);
	Line(_center, { _center.x + y, _center.y + x }, _color);
	Line(_center, { _center.x - y, _center.y + x }, _color);
	Line(_center, { _center.x + y, _center.y - x }, _color);
	Line(_center, { _center.x - y, _center.y - x }, _color);
	while (x <= y) //while x less or equal than y, meaning until we reach the 45degree coordinate after which x>y
	{
		++x; //increment x
		if (d < 0) //if decision parameter is less than 0, meaning the next pixel is east{x+1, y}
			d += (4 * x) + 6; //recalculate decision parameter with new X value(again [7] for proof)
		else //else decision parameter is >=0, meaning the next pixel is south-east{x+1, y-1}
		{
			d += 4 * (x - y) + 10; // [7]
			y--; //decrement x
		}
		//draw pixel for every octant
		Line(_center, { _center.x + x, _center.y + y }, _color);
		Line(_center, { _center.x - x, _center.y + y }, _color);
		Line(_center, { _center.x + x, _center.y - y }, _color);
		Line(_center, { _center.x - x, _center.y - y }, _color);
		Line(_center, { _center.x + y, _center.y + x }, _color);
		Line(_center, { _center.x - y, _center.y + x }, _color);
		Line(_center, { _center.x + y, _center.y - x }, _color);
		Line(_center, { _center.x - y, _center.y - x }, _color);
	}
	//for (;r > 0; r--)
	//{
	//	DrawCircleOutline(_center, r, _color);
	//}
}
void Shape2D::DrawCircleFilledLoop(glm::vec2 _center, int r, glm::vec3 _color)
{
	for (;r > 0; r--)
	{
		DrawCircleOutline(_center, r, _color);
	}
}
void Shape2D::DrawCircleGradient(glm::vec2 _center, int r, glm::vec3 _c1, glm::vec3 _c2)
{
	glm::vec3 result;
	for (int stepX = 1; stepX < r; stepX++)
	{
		result.x = (_c2.x - _c1.x) * stepX / r + _c1.x;
		result.y = (_c2.y - _c1.y) * stepX / r + _c1.y;
		result.z = (_c2.z - _c1.z) * stepX / r + _c1.z;
		DrawCircleOutline(_center, stepX, result);
	}
}
void Shape2D::DrawCircleUnit(glm::vec2 _center, int _r, glm::vec3 _color)
{
	glm::vec2 pixel;
	for (float rad = 0.0f; rad < 2 * PI; rad += 0.01f)
	{
		pixel.x = _center.x + (_r * (cosf(rad)));
		pixel.y = _center.y + (_r * (sinf(rad)));
		MCG::DrawPixel(pixel, _color);
	}
}
