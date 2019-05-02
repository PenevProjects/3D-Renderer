#include <iostream>
#include <cmath>
#include <ctime>
#include <windows.h>
#include "Shape.h"
#include "conio.h"
#include "MCG_GFX_Lib.h"


#define PI 3.14159265358979323846264338327950288419716939937510582097494459230781640628620899862803482534211706798214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196442881097566593344612847564823378678316527120190914564856692346034861045432664821339360726024914127372458700660631558817488152092096282f



void Line(glm::ivec2 _a, glm::ivec2 _b, glm::vec3 color);
void DrawTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color);
void fillBottomFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color);
void fillTopFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color);
void FillTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color);


typedef glm::vec3 Point3;
typedef glm::vec2 Point2;

struct triangle
{
	Point3 p[3];
};

int main(int argc, char *argv[])
{
	srand(unsigned(time(NULL)));

	glm::ivec2 windowSize(640, 480);


	if (!MCG::Init(windowSize))
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}



	MCG::SetBackground(glm::ivec3(0, 0, 0));
	glm::vec3 pixelColour(255, 255, 255);
	glm::ivec2 pixelPosition = windowSize / 2;

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





	float timer = 0.0f;


	std::unique_ptr<Shape> Circle{ new Shape() };

	float scalar = 1.02f;

	glm::mat2 matx = { 1.02f, 0,
	0, 1.02f };

	int radius = 50;
	float rad = 0.0f;
	for (float rad = 0.0f; rad < 2 * PI; rad += 0.01f)
	{
		Circle->pushbackPosition(int(70 + (radius*(cos(rad)))), int(70 + (radius * (sin(rad)))));
	}


	std::vector<triangle> mesh = {
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


	//variables for perspective projection matrix
	float zNear = 0.1f; //nearest point on Z-plane
	float zFar = 100.0f; // furthest point on Z-plane
	float FOV = 90.0f * PI / 180.0f; // FOV in radians
	float fAspectRatio = (float)windowSize.x / (float)windowSize.y; //aspect ratio

	
	glm::mat4x4 projMat{ glm::perspective(FOV, fAspectRatio, zNear, zFar) };

	glm::mat4x4 trimodelMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 5.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	glm::mat4x4 lmodelMatrix = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, -2.0f,
		0.0f, 0.0f, 0.0f, 1.0f };

	glm::vec3 camera{ 0.0f, 0.0f, -3.0f };
	glm::mat4x4 viewMatrix = glm::lookAt(camera, { 0.0f, 0.0f, 0.0f }, { 0.0f, -1.0f, 0.0f });


	glm::vec4 viewport = { 0, 0, windowSize.x, windowSize.y };

	glm::vec3 lightPos(0.0f, 0.0f, -25.0f); //lighting position
	glm::vec3 lightIntensity = { 1.0f,1.0f,1.0f }; //lighting intensity

	while( MCG::ProcessFrame() )
	{
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );
		timer += 1.0f / 60.0f;

		//rotation in Z
		glm::mat4x4 matRotZ = { cosf(timer), -sinf(timer), 0, 0,
					   sinf(timer), cosf(timer), 0,0,
					   0,0,1,0,
					   0,0,0,1 };

		//rotation in X is slower to avoid gimble lock
		glm::mat4x4 matRotX = { 1, 0, 0, 0,
			   0, cosf(timer*0.5f), -sinf(timer *0.5f),0,
			   0, sinf(timer*0.5f),cosf(timer*0.5f),0,
			   0,0,0,1 };

		


		for (auto tri : mesh)
		{
			triangle triModel, triProjected, triRotatedZ, triRotatedZX, triScaled;

			//make object spin while still in object space, first Z axis then X to avoid gimble lock
			triRotatedZ.p[0] = matRotZ * glm::vec4(tri.p[0], 1);
			triRotatedZ.p[1] = matRotZ * glm::vec4(tri.p[1], 1);
			triRotatedZ.p[2] = matRotZ * glm::vec4(tri.p[2], 1);
			triRotatedZX.p[0] = matRotX * glm::vec4(triRotatedZ.p[0], 1);
			triRotatedZX.p[1] = matRotX * glm::vec4(triRotatedZ.p[1], 1);
			triRotatedZX.p[2] = matRotX * glm::vec4(triRotatedZ.p[2], 1);

			// convert object's vertices from object space to world space through multiplying it by its model matrix
			triModel.p[0] = trimodelMatrix * glm::vec4(triRotatedZX.p[0], 1);
			triModel.p[1] = trimodelMatrix * glm::vec4(triRotatedZX.p[1], 1);
			triModel.p[2] = trimodelMatrix * glm::vec4(triRotatedZX.p[2], 1);

			//find normals in model space(required for lighting)
			glm::vec3 modNorm, modSide, modSide2; 
			modSide = triModel.p[1] - triModel.p[0]; //find 1 side of triangle connecting in p0
			modSide2 = triModel.p[2] - triModel.p[0]; //find second side of triangle connecting in p0
			modNorm = glm::cross(modSide, modSide2); //cross product of the two sides of the triangle to find normal
			modNorm = glm::normalize(modNorm); //normalize the normal because we need only its direction

			glm::vec3 lightDir = lightPos - triModel.p[0]; //light direction is lightposition - p[0] vertex
			lightDir = lmodelMatrix * glm::vec4(lightDir, 1); //convert lightDirection into world coordinates
			lightDir = glm::normalize(lightDir); //normalize lightDirection because we need only its direction

			//project vertices into projection space
			triProjected.p[0] = glm::project(triRotatedZX.p[0], trimodelMatrix * viewMatrix, projMat, viewport); 
			triProjected.p[1] = glm::project(triRotatedZX.p[1], trimodelMatrix * viewMatrix, projMat, viewport);
			triProjected.p[2] = glm::project(triRotatedZX.p[2], trimodelMatrix * viewMatrix, projMat, viewport);

			//find projection normal to use in calculation of which squares we can see(by dotting the normal and the camera vector)
			glm::vec3 projNormal, projSide1, projSide2;
			projSide1 = triProjected.p[1] - triProjected.p[0];
			projSide2 = triProjected.p[2] - triProjected.p[0];
			projNormal = glm::cross(projSide1, projSide2);
			projNormal = glm::normalize(projNormal);


			float lumFraction = glm::max(glm::dot(modNorm, lightDir), 0.0f); //luminosity fraction = dotted product of model space normal and light direction
			glm::vec3 lum = lumFraction * lightIntensity; //find luminosity value by multiplying fraction and intensity


			if (glm::dot(projNormal, camera) < 0.0f) // if dotted product is positive, we can't see the triangle as angle between normal and camera is acute
				FillTriangle(
					triProjected.p[0],
					triProjected.p[1],
					triProjected.p[2],
					glm::vec3(255, 135, 185) * lum);
		}




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
	

	//_getch();
	//_getch();
	//return 0;
	

}
void Line(glm::ivec2 _a, glm::ivec2 _b, glm::vec3 color) //utilizing Bresenham's algorithm
{
	int dx, dy; //delta x, delta y
	int stepx, stepy; //x step, y step

	dx = _b.x - _a.x; // change in x
	dy = _b.y - _a.y; // change in y

	if (dy < 0) // if change in y is less than 0, y0 > y1, meaning line goes up and right
	{
		dy = -dy; //need negative of m from y = mx + c, so dy = -dy
		stepy = -1; //step by going upwards instead of downwards
	}
	else
		stepy = 1; // step by going down
	if (dx < 0) // x0 > x1, meaning right to left
	{
		dx = -dx; //need negative of m
		stepx = -1; // step by going right to left
	}
	else
	{
		stepx = 1; // step by going left to right
	}


	if (dx > dy)
	{
		int fraction = (dy * 2) - dx; // see references for proof of initial fraction value
		while (_a.x != _b.x) // while y0 is different than y1
		{
			MCG::DrawPixel(glm::vec2(_a.x, _a.y), color);
			_a.x += stepx; //increment x
			if (fraction >= 0) //if fraction is positive, we have reached the y change
			{
				_a.y += stepy; //increment y
				fraction -= dx; //subtract dx from fraction (from dx > dy)
			}
			fraction += dy; //add dy to fraction to keep track when we need to increment y

		}
	}
	else //when dy > dx
	{
		/* vice versa from the if statement*/
		int fraction = (dx * 2) - dy;
		while (_a.y != _b.y)
		{

			MCG::DrawPixel(glm::vec2(_a.x, _a.y), color);
			_a.y += stepy;
			if (fraction >= 0)
			{
				_a.x += stepx;
				fraction -= dy;
			}
			fraction += dx;
		}
	}
}
void DrawTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color)
{
	Line({ v1.x, v1.y }, { v2.x, v2.y }, color);
	Line({ v2.x, v2.y }, { v3.x, v3.y }, color);
	Line({ v3.x, v3.y }, { v1.x, v1.y }, color);
}
void fillBottomFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color) // function to fill bottomflat triangle
{
	/* will need the change in X for both lines that connect in point v1,
	m = dx/dy which is 1/m, we need change in X per step in Y 
	this algorithm utilizes top-left rasterization rule*/
	float slope1 = (v2.x - v1.x) / (v2.y - v1.y); // left line slope
	float slope2 = (v3.x - v1.x) / (v3.y - v1.y); // right line slope

	int startY = (int)ceil(v1.y - 0.5f); //scanline's Y of first line( subtract 0.5f because we are calculating based on pixel centers, implementing top part of top-left rule)
	int endY = (int)ceil(v3.y - 0.5f); //scanline's Y after last line drawn( subtract 0.5f because we are calculating based on pixel centers, implementing top part of top-left rule)

	for (int currentY = startY; currentY < endY; currentY++)
	{
		float currentX0 = slope1 * (currentY + 0.5f - v2.y) + v2.x; // calculate current X by: Divide the distance from starting point to the currentY, by deltaY, multiply that by deltaX then add v1.x
		float currentX1 = slope2 * (currentY + 0.5f - v3.y) + v3.x; // calculate current X by: Divide: (the distance from starting point to the currentY), by deltaY, multiply that by deltaX then add v1.x

		int xStart = (int)ceil(currentX0 - 0.5f); //scanline's starting X, implementing left part of top-left rule
		int xEnd = (int)ceil(currentX1 - 0.5f); //scanline's last X implementing left part of top-left rule
		Line({ xStart, currentY }, { xEnd, currentY }, color); // draws line between current xStart and xEnd at the current Y value
	}
}
void fillTopFlatTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color) // function to fill topflat triangle
{
	/* will need the change in X for both lines that connect in point v3,
	m = dx/dy which is 1/m, we need change in X per step in Y
	this algorithm utilizes top-left rasterization rule*/
	float slope1 = (v3.x - v1.x) / (v3.y - v1.y); // left line slope
	float slope2 = (v3.x - v2.x) / (v3.y - v2.y); // right line slope

	int startY = (int)ceil(v1.y - 0.5f); //scanline's Y of first line( subtract 0.5f because we are calculating based on pixel centers, implementing top part of top-left rule)
	int endY = (int)ceil(v3.y - 0.5f); //scanline's Y after last line drawn

	for (int currentY = startY; currentY < endY; currentY++)
	{
		float currentX0 = slope1 * (currentY + 0.5f - v1.y) + v1.x; // calculate current X by: Divide the distance from starting point to the currentY, by deltaY, multiply that by deltaX then add v1.x
		float currentX1 = slope2 * (currentY + 0.5f - v2.y) + v2.x; // calculate current X by: Divide: (the distance from starting point to the currentY), by deltaY, multiply that by deltaX then add v1.x

		int xStart = (int)ceil(currentX0 - 0.5f); //scanline's starting X, implementing left part of top-left rule
		int xEnd = (int)ceil(currentX1 - 0.5f); //scanline's last X
		Line({ xStart, currentY }, { xEnd, currentY }, color); // draws line between current xStart and xEnd at the current Y value
	}
}
void FillTriangle(glm::vec2 v1, glm::vec2 v2, glm::vec2 v3, glm::vec3 color)
{
	//sort
	if (v1.y > v2.y) std::swap(v1, v2);
	if (v1.y > v3.y) std::swap(v1, v3);
	if (v2.y > v3.y) std::swap(v2, v3);


	if (v2.y == v3.y) // flat bottom
	{
		if (v3.x < v2.x) std::swap(v2, v3); // sorting bottom vertices by x
		fillBottomFlatTriangle(v1, v2, v3, color);
	}
	else if (v1.y == v2.y) // flat top
	{
		if (v2.x < v1.x) std::swap(v1, v2); // sorting top vertices by x
		fillTopFlatTriangle(v1, v2, v3, color);
	}
	else
	{
		//find splitting vertex
		float ratio = (v2.y - v1.y) / (v3.y - v1.y); //ratio between 2 sides
		glm::vec2 vSplit = v1 + (v3-v1) * ratio;

		if (v2.x < vSplit.x) // major right triangle
		{
			fillBottomFlatTriangle(v1, v2, vSplit, color);
			fillTopFlatTriangle(v2, vSplit, v3, color);
		}
		else // major left triangle
		{
			fillBottomFlatTriangle(v1, vSplit, v2, color);
			fillTopFlatTriangle(vSplit, v2, v3, color);
		}
	}
}