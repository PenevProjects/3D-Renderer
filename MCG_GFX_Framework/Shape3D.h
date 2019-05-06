#include <vector>
#include "MCG_GFX_Lib.h"
#include "TriangleClass.h"
#include <string>
#include <fstream>
#include <sstream>

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
		0.0f, 0.0f, 0.0f, 1.0f }; //modelling matrix for the triangles in mesh (initialized here with example values)

public:
	Shape3D(glm::vec3 _color);
	Shape3D(const Shape3D& _copy);
	~Shape3D();
	std::vector<triangle> getMesh() const;
	void Shape3D::setMeshFromFile(std::string sFilename);
	void Shape3D::setMesh(std::vector<triangle> _mesh);

	glm::vec3 getColor() const;
	void setColor(glm::vec3);

	glm::mat4x4 getModelMatrix() const;
	void setModelMatrix(glm::mat4x4 _matrix);

	void setRotationX(float dt);
	glm::mat4x4 getRotationX() const;
	void setRotationZ(float dt);
	glm::mat4x4 getRotationZ() const;

};

