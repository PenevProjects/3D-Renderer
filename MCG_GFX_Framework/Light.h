#include "MCG_GFX_Lib.h"

#pragma once
class Light
{
private:
	glm::mat4x4 lmodelMatrix = {
	1.0f, 0.0f, 0.0f, 0.0f,
	0.0f, 1.0f, 0.0f, 0.0f,
	0.0f, 0.0f, 1.0f, -2.0f,
	0.0f, 0.0f, 0.0f, 1.0f };
	glm::vec3 lightPos{ 0.0f, 0.0f, -5.0f }; //lighting position
	glm::vec3 lightIntensity{ 1.0f,1.0f,1.0f }; //lighting intensity
	glm::vec3 lightDir; //lighting direction
	glm::vec3 lum; //luminosity value
public:
	Light();
	~Light();
	void setLightDir(glm::vec3 _vertice);
	glm::vec3 getLightDir();
	void setLum(glm::vec3 _normal, glm::vec3 _light);
	glm::vec3 getLum();
};

