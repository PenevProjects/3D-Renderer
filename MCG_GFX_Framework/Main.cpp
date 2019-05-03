#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <conio.h>

#include "MCG_GFX_Lib.h"

#include "Shape2D.h"
#include "TriangleClass.h"
#include "Renderer.h"
#include "Shape3D.h"



int main(int argc, char *argv[])
{
	srand(unsigned(time(NULL)));

	glm::ivec2 windowSize(640, 480);

	if (!MCG::Init(windowSize))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		std::cout << "Error initializing graphics library";
		return -1;
	}



	MCG::SetBackground(glm::ivec3(0, 0, 0));
	glm::vec3 pixelColour(255, 255, 255);
	glm::ivec2 pixelPosition = windowSize / 2;

	TriangleClass triObject;
	Renderer renderer;

	renderer.setWindowSize(windowSize);

	/*

	*/
	//unit circle

	//for (float rad = 0.0f; rad < 2 * PI; rad += 0.01f)
	//{
	//	//CirclePoint.x = 100 + (radius * (cos(rad)));
	//	//CirclePoint.y = 100 + (radius * (sin(rad)));
	//	example.pushbackPosition(int(100 + (radius*(cos(rad)))), int(100 + (radius * (sin(rad)))));
	//}

	/*return MCG::ShowAndHold();*/





	float dt = 0.0f;


	//std::unique_ptr<Shape> Circle{ new Shape() };

	//float scalar = 1.02f;

	//glm::mat2 matx = { 1.02f, 0,
	//0, 1.02f };

	//int radius = 50;
	//float rad = 0.0f;
	//for (float rad = 0.0f; rad < 2 * PI; rad += 0.01f)
	//{
	//	Circle->pushbackPosition(int(70 + (radius*(cos(rad)))), int(70 + (radius * (sin(rad)))));
	//}

	Shape3D cube3D;

	std::vector<triangle> cubeMesh = {
		//mesh of a cube, triangles always drawn in clockwise direction to make sure normals point outwards
		//south
		{glm::vec3(0.0f, 0.0f, 0.0f),   glm::vec3(0.0f, 1.0f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f)},
		{glm::vec3(0.0f, 0.0f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f)},

		//east
		{glm::vec3(1.0f, 0.0f, 0.0f),   glm::vec3(1.0f, 1.0f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f)},
		{glm::vec3(1.0f, 0.0f, 0.0f),  glm::vec3(1.0f, 1.0f, 1.0f),   glm::vec3(1.0f, 0.0f, 1.0f)},

		//north
		{glm::vec3(1.0f, 0.0f, 1.0f),   glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 1.0f)},
		{glm::vec3(1.0f, 0.0f, 1.0f),   glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 1.0f)},

		//west
		{glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f)},
		{glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(0.0f, 1.0f, 0.0f),   glm::vec3(0.0f, 0.0f, 0.0f)},

		//top
		{glm::vec3(0.0f, 1.0f, 0.0f),   glm::vec3(0.0f, 1.0f, 1.0f),   glm::vec3(1.0f, 1.0f, 1.0f)},
		{glm::vec3(0.0f, 1.0f, 0.0f),   glm::vec3(1.0f, 1.0f, 1.0f),  glm::vec3(1.0f, 1.0f, 0.0f)},

		//bottom
		{glm::vec3(1.0f, 0.0f, 1.0f),   glm::vec3(0.0f, 0.0f, 1.0f),  glm::vec3(0.0f, 0.0f, 0.0f)},
		{glm::vec3(1.0f, 0.0f, 1.0f),   glm::vec3(0.0f, 0.0f, 0.0f),   glm::vec3(1.0f, 0.0f, 0.0f)},
	};

	//use this if you want to set a different model matrix
	//cube3D.setModelMatrix(); 



	while( MCG::ProcessFrame() )
	{
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );
		dt += 1.0f / 60.0f;
		cube3D.setMesh(cubeMesh);
		cube3D.setRotationX(dt);
		cube3D.setRotationZ(dt);

		renderer.RenderShape(&cube3D);


		//for (std::size_t i = 1; i < Circle->getPositionVector().size(); i++)
		//{
		//	MCG::DrawPixel(Circle->getPosition(int(i)), pixelColour);
		//}

		//for (std::size_t i = 0; i < Circle->getPositionVector().size(); i++)
		//{
		//	Circle->getPosition(int(i)) = Circle->getPosition(int(i)) * matx;
		//}
		
		/*MCG::DrawPixel(example.getPosition(int(timer*60.0f)), pixelColour);*/
		/*MCG::DrawPixel( pixelPosition, pixelColour );*/

	}
}