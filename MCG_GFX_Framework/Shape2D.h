#include <vector>
#include "MCG_GFX_Lib.h"
#include "TriangleClass.h"
#include <iostream>

#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282f

#pragma once
class Shape2D 
	: public TriangleClass
{
private:
	glm::vec3 color;
	std::vector<glm::vec2> PositionVec; //can be used if you want to store the shape into a vector, useful for brute-forcing custom shapes, however slow and resource-heavy
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

	void DrawBezierCurve(glm::vec2 _p1, glm::vec2 _p2, glm::vec2 _c1, glm::vec2 _c2);

	void DrawSquareGradient(int _len, glm::vec3 _c1, glm::vec3 _c2);
	void DrawSquareFilled(int _len);
	void DrawSquareOutline(glm::ivec2 topLeft, glm::ivec2 botRight);

	void DrawCircleUnit(glm::vec2 _center, int _r); //unit circle drawing algorithm, inaccurate, slow and wastes a lot of resources(cos and sin calculations)
	void DrawCircleOutline(glm::vec2 _center, int r); //bresenham midpoint circle drawing algorithm, faster and more accurate
	void DrawCircleFilledBres(glm::vec2 _center, int r); //drawing filled circle by running lines from origin to endpoint, inaccuracies... to be worked on
	void DrawCircleFilledLoop(glm::vec2 _center, int r); //drawing filled circle by drawing many outline circles, inaccuracies... to be worked on
	void DrawCircleGradient(glm::vec2 _center, int r, glm::vec3 _c1, glm::vec3 _c2); //color interpolation algorithm + DrawCircleFilledLoop()
};

