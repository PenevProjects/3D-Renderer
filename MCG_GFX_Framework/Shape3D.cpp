#include "Shape3D.h"



Shape3D::Shape3D(const Shape3D& _copy) 
	: color(_copy.getColor()),
	triModelMatrix(_copy.getModelMatrix()),
	mesh(_copy.getMesh())
{
}

Shape3D::Shape3D(glm::vec3 _color)
{
	color = _color;
}


Shape3D::~Shape3D()
{
}

glm::vec3 Shape3D::getColor() const
{
	return color;
}
void Shape3D::setColor(glm::vec3 _color)
{
	color = _color;
}

std::vector<triangle> Shape3D::getMesh() const
{
	return mesh;
}
void Shape3D::setMesh(std::vector<triangle> _mesh)
{
	mesh = _mesh;
}


glm::mat4x4 Shape3D::getModelMatrix() const
{
	return triModelMatrix;
}
void Shape3D::setModelMatrix(glm::mat4x4 _matrix)
{
	triModelMatrix = _matrix;
}
void Shape3D::setRotationX(float dt)
{
	//rotation in X is slower than in Z to avoid gimble lock
	RotationX = { 1, 0, 0, 0,
	   0, cosf(dt*0.5f), -sinf(dt*0.5f),0,
	   0, sinf(dt*0.5f),cosf(dt*0.5f),0,
	   0,0,0,1 };
}

glm::mat4x4 Shape3D::getRotationX() const
{
	return RotationX;
}

void Shape3D::setRotationZ(float dt)
{
	RotationZ = { cosf(dt), -sinf(dt), 0, 0,
			   sinf(dt), cosf(dt), 0,0,
			   0,0,1,0,
			   0,0,0,1 };
}

glm::mat4x4 Shape3D::getRotationZ() const
{
	return RotationZ;
}