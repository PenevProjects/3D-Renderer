#include <vector>
#include <iostream>

#include "MCG_GFX_Lib.h"
#include "TriangleClass.h"
#include "Shape3D.h"
#include "Light.h"



#pragma once

#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282f

class Renderer
{
private:
	glm::ivec2 windowSize = { 640,480 };
	float zNear = 0.1f; //nearest point on Z-plane
	float zFar = 100.0f; // furthest point on Z-plane
	float FOV = 90.0f * PI / 180.0f; // FOV in radians
	float fAspectRatio = (float)windowSize.x / (float)windowSize.y; //aspect ratio

	std::vector<triangle> mesh; //object mesh

	glm::mat4x4 projMat; //projection matrix

	glm::vec3 camera{ 0.0f, 0.0f, -3.0f }; //camera location
	glm::mat4x4 viewMatrix = glm::lookAt(camera, { 0.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }); //viewing matrix
	glm::vec4 viewport = { 0, 0, windowSize.x, windowSize.y }; //viewport
public:
	Renderer();
	~Renderer();
	void setWindowSize(glm::ivec2 _wSize);
	glm::ivec2 getWindowSize() const;
	void RenderShape(Shape3D* _shape);
};

