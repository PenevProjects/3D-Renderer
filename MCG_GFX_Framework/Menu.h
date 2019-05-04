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

#pragma once
class Menu
{
private:
	glm::ivec2 windowSize{ 640,480 };
public:
	Menu();
	~Menu();
	void Run();
	void Render(glm::ivec2 _wSize, Shape3D cube3D);
	int Selection(int min, int max);
	void Initialize(glm::ivec2 _wSize);
};

