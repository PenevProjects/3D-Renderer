#include <vector>
#include "MCG_GFX_Lib.h"
#include "TriangleClass.h"

#pragma once

class Shape3D :
	public TriangleClass
{
private:
	glm::vec3 color;
	//mesh vector
	std::vector<triangle> mesh;

	glm::mat4x4 RotationX;
	glm::mat4x4 RotationZ;

	glm::mat4x4 triModelMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 5.0f,
		0.0f, 0.0f, 0.0f, 1.0f }; //modelling matrix for the triangles in mesh (initialized with default values for renderer)

public:
	Shape3D();
	Shape3D(glm::vec3 _color);
	~Shape3D();
	std::vector<triangle> getMesh() const;
	void setMesh(std::vector<triangle> _mesh);

	glm::vec3 getColor();
	void setColor(glm::vec3);

	glm::mat4x4 getModelMatrix() const;
	void setModelMatrix(glm::mat4x4 _matrix);

	void setRotationX(float dt);
	glm::mat4x4 getRotationX() const;
	void setRotationZ(float dt);
	glm::mat4x4 getRotationZ() const;

};

