#include "Menu.h"



Menu::Menu(glm::ivec2 _wSize) 
	: windowSize(_wSize)
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
		std::cout << "Select shape: \n1. 3D Cube \n2. 3D Sphere\n3. Triangle \n4. Square \n5. Circle \n6. Line \n7. Bezier curve \n8. Exit";
		switch (Selection(0, 8))
		{
			case 1: //3d renderer
			{
				glm::vec3 color{ 0,212,255 };
				Initialize(windowSize);
				Shape3D cube3D(color);
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

				cube3D.setMesh(cubeMesh); //here we define the mesh manually on line 29
				//cube3D.setMeshFromFile("Cube.txt"); //uncomment this to define the mesh through a file
				Render(windowSize, cube3D);
				MCG::Cleanup();
				break;
			}
			case 2:
			{
				glm::vec3 color{ 43,140,255 };
				Initialize(windowSize);
				Shape3D sphere3D(color);
				sphere3D.setMeshFromFile("Sphere.txt");
				//you can also import your own objects, as long as they are .obj and with triangulated faces.
				//please note that this renderer has no Z-buffer so more complex objects will not render properly!
				//I used Blender export with only triangulated faces selected as an option.
				//shape.setModelMatrix();  //use this if you want to set a different model matrix
				Render(windowSize, sphere3D);
				MCG::Cleanup();
				break;

			}
			case 3: //triangle
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
			case 4: //square
			{
				Shape2D square({ 255,0,65 });
				std::cout << "Select option: \n1. Gradient filled \n2. Monotone filled \n3. Outline \n";
				glm::ivec2 start{ 150,150 };
				int length = 200;
				switch (Selection(0, 3))
				{
					case 1:
					{
						Initialize(windowSize);
						square.DrawSquareGradient(start, length, square.getColor(), { 0, 119, 255 });
						break;
					}
					case 2:
					{
						Initialize(windowSize);
						square.DrawSquareFilled(start, length);
						break;
					}
					case 3:
					{
						Initialize(windowSize);
						square.DrawSquareOutline(start, length);
						break;
					}
				}
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 5: //circle
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
						circle.DrawCircleFilledLoop({ 320,240 }, 100);
						break;
					}
					case 3:
					{
						Initialize(windowSize);
						circle.DrawCircleFilledBres({ 320,240 }, 100);
						break;
					}
					case 4:
					{
						//cos and sin operations, slow
						Initialize(windowSize);
						glm::vec2 pixelPos;
						for (int i = 100; i > 0; i--)
						{
							circle.DrawCircleUnit({ 320, 240 }, i);
						}
						break;
					}
					case 5:
					{
						//showcasing the inaccuracies in unit circle algorithm
						Initialize(windowSize);
						circle.DrawCircleOutline({ 200,240 }, 100);
						circle.DrawCircleUnit({ 440, 240 }, 100);
						break;
					}
				}
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 6: //line
			{
				TriangleClass oneline; //ha!
				Initialize(windowSize);
				oneline.Line({ 120, 400 }, { 380, 120 }, { 0,150,250 });
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 7: //bezier curve
			{
				Initialize(windowSize);
				Shape2D bezier({ 0, 255, 0 });
				bezier.DrawBezierCurve({ 200,200 }, { 500, 200 }, { 300, 80 }, { 400, 350 });
				MCG::ShowAndHold();
				MCG::Cleanup();
				break;
			}
			case 8: //exit
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
	Renderer renderer(windowSize);
	while (MCG::ProcessFrame())
	{
		MCG::SetBackground(glm::ivec3(0, 0, 0));
		dt += 1.0f / 60.0f;
		_shape.setRotationX(dt);
		_shape.setRotationZ(dt);
		renderer.RenderShape(&_shape);
	}
}