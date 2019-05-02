#include <vector>
#include "MCG_GFX_Lib.h"
#pragma once
class Shape
{
private:
	std::vector<glm::vec2> Position;
public:
	Shape();
	Shape(const Shape& t);
	virtual ~Shape();

	void pushbackPosition(int x, int y);

	std::vector<glm::vec2> getPositionVector();
	glm::vec2& getPosition(int i);
};

