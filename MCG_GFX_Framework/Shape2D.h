#include <vector>
#include "MCG_GFX_Lib.h"
#include "TriangleClass.h"
#include <iostream>

#pragma once
class Shape2D 
	: public TriangleClass
{
private:
	glm::vec3 color;
	std::vector<glm::vec2> PositionVec;
public:
	Shape2D(glm::vec3 _color);
	Shape2D(const Shape2D& _copy);
	Shape2D(const Shape2D& _copy, glm::ivec3 _color);
	~Shape2D();

	glm::vec3 getColor() const;
	void setColor(glm::vec3 _color);

	void pushbackPosition(int x, int y);

	std::vector<glm::vec2> getPositionVector() const;
	glm::vec2& getPositionAt(int i);

	void DrawSquareOutline(glm::vec3 _color, glm::ivec2 topLeft, glm::ivec2 botRight);
	void DrawSquareFilled(glm::vec3 _color, int _len);
	void DrawSquareGradient(glm::vec3 _c1, glm::vec3 _c2, int _len);

	void DrawCircleOutline(glm::vec2 _center, int r, glm::vec3 _color); //bresenham midpoint circle drawing algorithm
	void DrawCircleFilledBres(glm::vec2 _center, int r, glm::vec3 _color); //drawing filled circle by running lines from origin to endpoint, inaccuracies... to be worked on
	void DrawCircleFilledLoop(glm::vec2 _center, int r, glm::vec3 _color); //drawing filled circle by drawing many outline circles, inaccuracies... to be worked on
	void DrawCircleGradient(glm::vec2 _center, int r, glm::vec3 _c1, glm::vec3 _c2);
};

