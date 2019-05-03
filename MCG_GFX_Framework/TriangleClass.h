#include "MCG_GFX_Lib.h"
#include <algorithm>
#pragma once

//structure of triangle
struct triangle
{
	glm::vec3 p[3];
};

//triangle operations class
class TriangleClass
{
public:
	TriangleClass();
	virtual ~TriangleClass();
	void Line(glm::ivec2 _a, glm::ivec2 _b, glm::vec3 color) ; //bresenham's line algorithm
	void DrawTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color); //based on line algorithm
	void fillBottomFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color); //rasterization for bottom flat triangle
	void fillTopFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color); //rasterization for top flat triangle
	void FillTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color); //rasterization algorithm
};

