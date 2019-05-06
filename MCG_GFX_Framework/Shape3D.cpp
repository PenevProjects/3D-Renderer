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
void Shape3D::setMeshFromFile(std::string sFilename)
{
	std::ifstream file(sFilename);

	std::vector<glm::vec3> vertices;

	while (!file.eof())
	{
		std::string line;
		std::getline(file, line, '\n');

		std::stringstream stream;
		stream << line;

		char first;
		if (line[0] == 'v')
		{
			glm::vec3 v;
			stream >> first >> v.x >> v.y >> v.z;
			vertices.push_back(v);
		}
		if (line[0] == 'f')
		{
			int f[3];
			stream >> first >> f[0] >> f[1] >> f[2];
			mesh.push_back({ vertices[f[0] - 1], vertices[f[1] - 1], vertices[f[2] - 1] });
		}
	}
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