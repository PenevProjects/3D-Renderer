#include "Renderer.h"

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::setWindowSize(glm::ivec2 _wSize)
{
	windowSize = _wSize;
}
glm::ivec2 Renderer::getWindowSize() const
{
	return windowSize;
}



void Renderer::RenderShape(Shape3D* _shape)
{
	Light _light;
	//rotation in z
	//rotation in X is slower to avoid gimble lock

	projMat = glm::perspective(FOV, fAspectRatio, zNear, zFar);

	if (_shape->getMesh().empty() == true) //make sure we are not rendering a non-existing object
	{
		std::cout << "Shape mesh not set. Aborting...";
		throw std::invalid_argument("shape mesh");
		return;
	}

	mesh = _shape->getMesh(); //assign renderer's mesh variable from shape

	for (auto tri : mesh)
	{
		triangle triModel, triProjected, triRotatedZ, triRotatedZX, triScaled;

		//make object spin while still in object space, first Z axis then in X axis slower to avoid gimble lock
		triRotatedZ.p[0] = _shape->getRotationZ() * glm::vec4(tri.p[0], 1);
		triRotatedZ.p[1] = _shape->getRotationZ() * glm::vec4(tri.p[1], 1);
		triRotatedZ.p[2] = _shape->getRotationZ() * glm::vec4(tri.p[2], 1);
		triRotatedZX.p[0] = _shape->getRotationX() * glm::vec4(triRotatedZ.p[0], 1);
		triRotatedZX.p[1] = _shape->getRotationX() * glm::vec4(triRotatedZ.p[1], 1);
		triRotatedZX.p[2] = _shape->getRotationX() * glm::vec4(triRotatedZ.p[2], 1);

		// convert object's vertices from object space to world space by multiplying it by its model matrix(required for lighting)
		triModel.p[0] = _shape->getModelMatrix() * glm::vec4(triRotatedZX.p[0], 1);
		triModel.p[1] = _shape->getModelMatrix() * glm::vec4(triRotatedZX.p[1], 1);
		triModel.p[2] = _shape->getModelMatrix() * glm::vec4(triRotatedZX.p[2], 1);

		//find normals in model space(required for lighting)
		glm::vec3 modNorm, modSide, modSide2;
		modSide = triModel.p[1] - triModel.p[0]; //find 1 side of triangle connecting in p0
		modSide2 = triModel.p[2] - triModel.p[0]; //find second side of triangle connecting in p0
		modNorm = glm::cross(modSide, modSide2); //cross product of the two sides of the triangle to find normal
		modNorm = glm::normalize(modNorm); //normalize the normal because we need only its direction

		_light.setLightDir(triModel.p[0]);

		//project vertices
		triProjected.p[0] = glm::project(triRotatedZX.p[0], _shape->getModelMatrix() * viewMatrix, projMat, viewport);
		triProjected.p[1] = glm::project(triRotatedZX.p[1], _shape->getModelMatrix() * viewMatrix, projMat, viewport);
		triProjected.p[2] = glm::project(triRotatedZX.p[2], _shape->getModelMatrix() * viewMatrix, projMat, viewport);

		//find projection normals to use in backface culling
		glm::vec3 projNormal, projSide1, projSide2;
		projSide1 = triProjected.p[1] - triProjected.p[0];
		projSide2 = triProjected.p[2] - triProjected.p[0];
		projNormal = glm::cross(projSide1, projSide2);
		projNormal = glm::normalize(projNormal);

		_light.setLum(modNorm, _light.getLightDir());


		if (glm::dot(projNormal, camera) < 0.0f) // if dotted product is positive, we can't see the triangle as angle between normal and camera is acute
			_shape->FillTriangle(
				triProjected.p[0],
				triProjected.p[1],
				triProjected.p[2],
				_shape->getColor() * _light.getLum());
	}
}