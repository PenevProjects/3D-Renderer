#include "Shape2D.h"



Shape2D::Shape2D()
{
}

Shape2D::Shape2D(const Shape2D& t) : PositionVec(t.PositionVec)
{
}

Shape2D::~Shape2D()
{
}

void Shape2D::pushbackPosition(int x, int y)
{
	PositionVec.push_back(glm::vec2(x, y));
}
std::vector<glm::vec2> Shape2D::getPositionVector()
{
	return PositionVec;
}
glm::vec2& Shape2D::getPosition(int i)
{
	return PositionVec.at(i);
}