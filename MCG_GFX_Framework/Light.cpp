#include "Light.h"



Light::Light()
{
}


Light::~Light()
{
}

void Light::setLightDir(glm::vec3 _vertex)
{
	lightDir = lightPos - _vertex; //light direction is lightposition - vertex
	lightDir = lmodelMatrix * glm::vec4(lightDir, 1); //convert lightDirection into world coordinates
	lightDir = glm::normalize(lightDir); //normalize lightDirection because we need only its direction
}
glm::vec3 Light::getLightDir()
{
	return lightDir;
}
void Light::setLum(glm::vec3 _normal, glm::vec3 _light)
{
	float lumFraction = glm::max(glm::dot(_normal, _light), 0.0f); //luminosity fraction = dotted product of model space normal and light direction
	lum = lumFraction * lightIntensity; //find luminosity value by multiplying fraction and intensity
}
glm::vec3 Light::getLum()
{
	return lum;
}