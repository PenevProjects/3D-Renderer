#include "Shape.h"



Shape::Shape()
{
}

Shape::Shape(const Shape& t) :
	Position(t.Position)
{
}

Shape::~Shape()
{
}

void Shape::pushbackPosition(int x, int y)
{
	Position.push_back(glm::vec2(x, y));
}
std::vector<glm::vec2> Shape::getPositionVector()
{
	return Position;
}
glm::vec2& Shape::getPosition(int i)
{
	return Position.at(i);
}