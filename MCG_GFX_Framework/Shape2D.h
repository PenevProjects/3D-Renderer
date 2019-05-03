#include <vector>
#include "MCG_GFX_Lib.h"
#pragma once
class Shape2D
{
private:
	std::vector<glm::vec2> PositionVec;
public:
	Shape2D();
	Shape2D(const Shape2D& t);
	virtual ~Shape2D();

	void pushbackPosition(int x, int y);

	std::vector<glm::vec2> getPositionVector();
	glm::vec2& getPosition(int i);
};

