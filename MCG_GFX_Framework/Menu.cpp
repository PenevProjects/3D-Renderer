#include "Menu.h"



Menu::Menu()
{
}


Menu::~Menu()
{
}

void Menu::Run()
{
	srand(unsigned(time(NULL)));
	bool exitFlag = false;
	while (exitFlag == false)
	{
		std::cout << "Select shape: \n1. 3D Cube \n2. Triangle \n3. Square \n4. Circle \n5. Line \n6. Exit \n";
		switch (Selection(0, 6))
		{
			case 1: //3d renderer
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
				//cube3D.setModelMatrix();  //use this if you want to set a different model matrix
				Render(windowSize, cube3D);
				MCG::Cleanup();
				break;
			}
			case 2: //triangle
			{
				TriangleClass tri;
				std::cout << "Select option: \n1. Filled \n2. Outline \n";
				switch (Selection(0, 2))
				{
					case 1:
					{
						Initialize(windowSize);
						tri.FillTriangle({ 150, 100 }, { 400, 210 }, { 300, 380 }, { 0, 131, 255 }); //example coordinates, can be changed freely
						break;
					}
					case 2:
					{
						Initialize(windowSize);
						tri.DrawTriangle({ 260, 120 }, { 180, 300 }, { 430, 160 }, { 76,255,0 }); //example coordinates, can be changed freely
						break;
					}
				}
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 3: //square
			{
				Shape2D square({ 255,0,65 });
				std::cout << "Select option: \n1. Gradient filled \n2. Monotone filled \n3. Outline \n";
				switch (Selection(0, 3))
				{
					case 1:
					{
						Initialize(windowSize);
						square.DrawSquareGradient(square.getColor(), { 0, 119, 255 }, 200);
						break;
					}
					case 2:
					{
						Initialize(windowSize);
						square.DrawSquareFilled(square.getColor(), 200);
						break;
					}
					case 3:
					{
						Initialize(windowSize);
						square.DrawSquareOutline(square.getColor(), { 100, 100 }, { 300, 300 });
						break;
					}
				}
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 4: //circle
			{
				Shape2D circle({ 255,0,65 });
				std::cout << "Select option: \n1. Gradient filled (with 2.'s method) \n2. Monotone filled (bresenham, outline circles loop) \n3. Monotone filled (bresenham, lines from origin to endpoint) \n4. Monotone filled (unit circle, outline circles loop) \n5. Outline (bresenham mid-point left, unit circle right) ";
				switch (Selection(0, 5))
				{
					case 1:
					{
						Initialize(windowSize);
						circle.DrawCircleGradient({ 320,240 }, 100, { 255, 255, 0 }, { 255,80,0 });
						break;
					}
					case 2:
					{
						Initialize(windowSize);
						circle.DrawCircleFilledLoop({ 320,240 }, 100, { 35,255,200 });
						break;
					}
					case 3:
					{
						Initialize(windowSize);
						circle.DrawCircleFilledBres({ 320,240 }, 100, { 35,255,200 });
						break;
					}
					case 4:
					{
						//cos and sin operations, slow
						Initialize(windowSize);
						glm::vec2 pixelPos;
						for (int i = 100; i > 0; i--)
						{
							circle.DrawCircleUnit({ 320, 240 }, i, { 0,255,255 });
						}
						break;
					}
					case 5:
					{
						//showcasing the inaccuracies in unit circle algorithm
						Initialize(windowSize);
						circle.DrawCircleOutline({ 200,240 }, 100, { 0,255,0 });
						circle.DrawCircleUnit({ 440, 240 }, 100, { 255,0,0 });
						break;
					}
				}
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 5: //line
			{
				TriangleClass oneline; //ha!
				Initialize(windowSize);
				oneline.Line({ 120, 400 }, { 380, 120 }, { 0,150,250 });
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 6: //exit
			{
				exitFlag = true;
				break;
			}
		}
	}
	MCG::Cleanup();
}
void Menu::Initialize(glm::ivec2 _wSize)
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

int Menu::Selection(int min, int max)
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
void Menu::Render(glm::ivec2 _wSize, Shape3D _shape)
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


