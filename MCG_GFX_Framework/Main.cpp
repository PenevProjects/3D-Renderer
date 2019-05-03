#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <string>
#include <vector>
#include <sstream>

#include "MCG_GFX_Lib.h"

#include "Shape2D.h"
#include "TriangleClass.h"
#include "Renderer.h"
#include "Shape3D.h"


void Render(glm::ivec2 _wSize, Shape3D cube3D);
int Selection(int min, int max);
void Initialize(glm::ivec2 _wSize);


int main(int argc, char *argv[])
{
	srand(unsigned(time(NULL)));
	glm::ivec2 windowSize(640, 480);
	bool exitFlag = false;
	while (exitFlag == false)
	{
		std::cout << "Select shape: \n1. 3D Cube \n2. Triangle \n3. Square \n4. Circle \n5. Line \n";
		switch (Selection(0, 6))
		{
			case 1:
			{
				Initialize(windowSize);
				Shape3D cube3D({ 0,212,255 });
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
				cube3D.setMesh(cubeMesh);
				//use this if you want to set a different model matrix
				//cube3D.setModelMatrix(); 
				Render(windowSize, cube3D);
				MCG::Cleanup();
				break;
			}
			case 2:
			{
				TriangleClass tri;
				std::cout << "Select option: \n1. Filled \n2. Outline \n";
				switch (Selection(0, 2))
				{
				case 1:
					Initialize(windowSize);
					tri.FillTriangle({ 150, 100 }, { 400, 210 }, { 300, 380 }, { 0, 131, 255 });
					MCG::ShowAndHold();
					MCG::Cleanup();
					break;
				case 2:
					Initialize(windowSize);
					tri.DrawTriangle({ 260, 120 }, { 180, 300 }, { 430, 160 }, { 76,255,0 });
					MCG::ShowAndHold();
					MCG::Cleanup();
					break;
				}
				break;
			}
			case 6:
			{
				exitFlag = true;
				break;
			}
		}
	}
	MCG::Cleanup();
}
void Initialize(glm::ivec2 _wSize)
{
	if (!MCG::Init(_wSize))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		std::cout << "Error initializing graphics library";
		return;
	}
	MCG::SetBackground(glm::ivec3(0, 0, 0));
}

int Selection(int min, int max)
{
	std::string input;
	int choice = 0;
	while (true) 
	{
		std::cout << "\n> ";
		std::getline(std::cin, input);
		std::stringstream InStream(input);
		if (InStream >> choice) //if stringstream successfully inserts data into the int
			if (choice >= min && choice <= max) // if is in range 0 < n < 6
				return choice;
		std::cout << "Please enter valid number. \n >";
	}
}
void Render(glm::ivec2 _wSize, Shape3D _shape)
{
	float dt = 0.0f;
	Renderer renderer;
	renderer.setWindowSize(_wSize);
	while (MCG::ProcessFrame())
	{
		MCG::SetBackground(glm::ivec3(0, 0, 0));
		dt += 1.0f / 60.0f;
		_shape.setRotationX(dt);
		_shape.setRotationZ(dt);
		renderer.RenderShape(&_shape);


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
